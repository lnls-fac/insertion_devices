#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <stdlib.h>
#include <fieldmap.h>
#include <API.h>


static const double electron_rest_energy = 510998.92811;  // [eV]
static const double light_speed          = 299792458;     // [m/s]

struct InputParameters{
  std::string fieldmap_filename;
  std::string kickmap_filename;
  double energy;
  double rk_step;
  int nrpts_x;
  int nrpts_y;
  double dynamic_aperture_x;
  double dynamic_aperture_y;
};

void read_input_file(std::string input_filename, bool& status, InputParameters& inputs){
  std::ifstream input_file(input_filename.c_str());
  std::string line;
  std::string delimiter = " ";
  std::vector<std::string> values;

  if (!input_file.is_open()){
    std::cout << "Can't open input file!" << std::endl;
    status = false;
  }
  else{
    while(!input_file.eof()){
      getline(input_file, line);
      if (line.find("#")!=0 && !line.empty()){
        values.push_back(line);
      }
    }
    if (values.size() != 8) {
      std::cout << "Invalid number of input parameters!" << std::endl;
      status = false;
    } else{
      inputs.dynamic_aperture_y   = (std::atof(values.back().c_str()))/1000.0; values.pop_back();
      inputs.dynamic_aperture_x   = (std::atof(values.back().c_str()))/1000.0; values.pop_back();
      inputs.nrpts_y              = std::atoi(values.back().c_str());          values.pop_back();
      inputs.nrpts_x              = std::atoi(values.back().c_str());          values.pop_back();
      inputs.rk_step              = std::atof(values.back().c_str());          values.pop_back();
      inputs.energy               = std::atof(values.back().c_str());          values.pop_back();
      inputs.kickmap_filename     = values.back();                             values.pop_back();
      inputs.fieldmap_filename    = values.back();
      status = true;
    }
  }
}

void calc_field_3D(FieldMap fieldmap, Vector3D<> r, Vector3D<>& b){
  Vector3D<> field;
  try {
    field = fieldmap.field3D(r);
  } catch (...){
    field.x = field.y = field.z = 0;
  }
  b = field;
}

void test_interpolation(FieldMap fieldmap){
  Vector3D<> r;
  Vector3D<> b_interp;
  Vector3D<> b_calc;
  std::vector<double> diff;
  int nrpts = 50;

  double xmax = fieldmap.x_max;
  double xmin = fieldmap.x_min;
  double ymax = fieldmap.y_max;
  double ymin = fieldmap.y_min;
  double zmax = fieldmap.z_max;
  double zmin = fieldmap.z_min;
  double dx = (xmax - xmin)/(double(nrpts)-1.0);
  double dy = (ymax - ymin)/(double(nrpts)-1.0);
  double dz = (zmax - zmin)/(double(nrpts)-1.0);

  for (int i=0; i < nrpts; i+=1){
    for (int j=0; j < nrpts; j+=1){
      for (int k=0; k < nrpts; k+=1){
        r.x = xmin + i*dx;
        r.y = ymin + j*dy;
        r.z = zmin + k*dz;
        calc_field_3D(fieldmap, r, b_interp);
        b_calc.x = r.x*r.y*r.z;
        b_calc.y = r.x*r.x;
        b_calc.z = 50*r.y - r.z*r.x;
        diff.push_back((b_interp.x - b_calc.x));
        diff.push_back((b_interp.y - b_calc.y));
        diff.push_back((b_interp.z - b_calc.z));
      }
    }
  }

  std::cout << std::endl;
  std::cout << "Test interpolation - Max diff: "<<*std::max_element(diff.begin(), diff.end()) << std::endl;
}

void grid(int nrpts_x, int nrpts_y, double aperture_x, double aperture_y, std::vector<double>& x, std::vector<double>& y){
  if (nrpts_x > 1){
    for(int j = 0; j < nrpts_x; j+=1){
      x.push_back(-aperture_x + j*(2.0*aperture_x/(double(nrpts_x) - 1.0)));
    }
  } else x.push_back(0);
  if (nrpts_y > 1){
    for(int i = 0; i < nrpts_y; i+=1){
      y.push_back(- aperture_y + i*(2.0*aperture_y/(double(nrpts_y) - 1.0)));
    }
  } else y.push_back(0);
}

void calc_brho(double energy, double& beta, double& brho){
  double gamma = energy / electron_rest_energy;
  beta  = std::sqrt(1.0 - 1.0 / (gamma * gamma));
  brho  = (beta * energy / light_speed);
}

void newton_lorentz_equation(FieldMap fieldmap, double alpha, Vector3D<> r, Vector3D<> p,  Vector3D<>& b, Vector3D<>& dr_ds, Vector3D<>& dp_ds){

  calc_field_3D(fieldmap, r, b);

  dr_ds.x = p.x;
  dr_ds.y = p.y;
  dr_ds.z = p.z;
  dp_ds.x = - alpha * (p.y * b.z - p.z * b.y);
  dp_ds.y = - alpha * (p.z * b.x - p.x * b.z);
  dp_ds.z = - alpha * (p.x * b.y - p.y * b.x);
}

void runge_kutta(FieldMap fieldmap, double brho, double beta, double s_step, double max_rz, Vector3D<> r, Vector3D<> p, Vector3D<>& kicks){

  double alpha = 1.0/brho/beta;
  double s = 0;
  int i = 0;

  Vector3D<> b;
  Vector3D<> kr1; Vector3D<> kp1; Vector3D<> r1; Vector3D<> p1;
  Vector3D<> kr2; Vector3D<> kp2; Vector3D<> r2; Vector3D<> p2;
  Vector3D<> kr3; Vector3D<> kp3; Vector3D<> r3; Vector3D<> p3;
  Vector3D<> kr4; Vector3D<> kp4;

  while (r.z < max_rz){
    newton_lorentz_equation(fieldmap, alpha, r, p, b, kr1, kp1);
    r1 = r + (s_step/2.0)* kr1;
    p1 = p + (s_step/2.0)* kp1;

    newton_lorentz_equation(fieldmap, alpha, r1, p1, b, kr2, kp2);
    r2 = r + (s_step/2.0)* kr2;
    p2 = p + (s_step/2.0)* kp2;

    newton_lorentz_equation(fieldmap, alpha, r2, p2, b, kr3, kp3);
    r3 = r + s_step* kr3;
    p3 = p + s_step* kp3;

    newton_lorentz_equation(fieldmap, alpha, r3, p3, b, kr4, kp4);

    r = r + (s_step/6.0)*(kr1 + 2.0*kr2 + 2.0*kr3 + kr4);
    p = p + (s_step/6.0)*(kp1 + 2.0*kp2 + 2.0*kp3 + kp4);
    s += s_step;
    i += 1;
    // trajectory
    //std::cout << r.x << " " << r.y << " " << r.z << " " << p.x << " " << p.y << " " << p.z << std::endl;
  }
  kicks = p;
}

void test_quadrupole_kick(double x, double brho, double kick_x, double& calc_kx){
  double L = 0.25; //[m]
  double G = 1.0;
  double K = G/brho;
  calc_kx = std::sqrt(K)*std::sin(std::sqrt(K)*L)*x;
}

void generate_kickmap_and_test_kick(InputParameters inputs){

  time_t now = time(0); char* date = ctime(&now);

  try{
    FieldMap fieldmap(inputs.fieldmap_filename);

    std::ofstream output_file(inputs.kickmap_filename.c_str());
    if(! output_file) {
      std::cout << "Can't open output file!" << std::endl;
    } else {
      std::vector<double> x; std::vector<double> y;
      grid(inputs.nrpts_x, inputs.nrpts_y, inputs.dynamic_aperture_x, inputs.dynamic_aperture_y, x, y);

      double beta; double brho;
      calc_brho(inputs.energy, beta, brho);

      double min_rz = fieldmap.z_min;
      double max_rz = fieldmap.z_max;
      double kick_x[y.size()][x.size()];
      double kick_y[y.size()][x.size()];
      Vector3D<> r(0.0, 0.0, min_rz);
      Vector3D<> p(0.0, 0.0, 1.0);
      Vector3D<> kicks;

      double calc_kick_x[y.size()][x.size()];
      double diff[y.size()][x.size()];
      double calc_kx;

      for(int i = 0; i < y.size(); i+=1){
        for(int j =0; j < x.size(); j+=1){
          r.x = x[j];
          r.y = y[i];
          runge_kutta(fieldmap, brho, beta, inputs.rk_step, max_rz, r, p, kicks);
          kick_x[i][j] = kicks.x;
          kick_y[i][j] = kicks.y;
          test_quadrupole_kick(x[j], brho, kicks.x, calc_kx);
          calc_kick_x[i][j] = calc_kx;
          diff[i][j] = calc_kx - kicks.x;
        }
      }

      output_file << "# KICKMAP" << std::endl;
      output_file << "# Author: Luana N. P. Vilela @ LNLS, Date: " << date;
      output_file << "# ID Length [m]" << std::endl;
      output_file << fieldmap.physical_length << std::endl;
      output_file << "# Number of Horizontal Points" << std::endl;
      output_file << inputs.nrpts_x << std::endl;
      output_file << "# Number of Vertical Points" << std::endl;
      output_file << inputs.nrpts_y << std::endl;
      output_file << "# Horizontal KickTable in T2m2" << std::endl;
      output_file << "START" << std::endl;
      output_file << std::setw(14) << " ";

      for(int j =0; j < x.size(); j+=1){
          output_file << std::scientific << std::showpos << x[j] << " ";
      }
      output_file << std::endl;
      for(int i = 0; i < y.size(); i+=1){
        output_file << std::scientific << std::showpos << y[i] << " ";
        for(int j =0; j < x.size(); j+=1){
          output_file << std::scientific << std::showpos << kick_x[i][j] << " ";
        }
        output_file << std::endl;
      }

      output_file << "# Calc Horizontal KickTable in T2m2" << std::endl;
      output_file << "START" << std::endl;
      output_file << std::setw(14) << " ";
      for(int j =0; j < x.size(); j+=1){
          output_file << std::scientific << std::showpos << x[j] << " ";
      }
      output_file << std::endl;
      for(int i = 0; i < y.size(); i+=1){
        output_file << std::scientific << std::showpos << y[i] << " ";
        for(int j =0; j < x.size(); j+=1){
          output_file << std::scientific << std::showpos << calc_kick_x[i][j] << " ";
        }
        output_file << std::endl;
      }

      output_file << "# Diff Horizontal KickTable in T2m2" << std::endl;
      output_file << "START" << std::endl;
      output_file << std::setw(14) << " ";
      for(int j =0; j < x.size(); j+=1){
          output_file << std::scientific << std::showpos << x[j] << " ";
      }
      output_file << std::endl;
      for(int i = 0; i < y.size(); i+=1){
        output_file << std::scientific << std::showpos << y[i] << " ";
        for(int j =0; j < x.size(); j+=1){
          output_file << std::scientific << std::showpos << diff[i][j] << " ";
        }
        output_file << std::endl;
      }

      std::cout << std::endl;
      std::cout << "Test quadrupole kick: result in file " << inputs.kickmap_filename.c_str() << std::endl << std::endl;

    }
  }
  catch(...){
    std::cout << "Can't open fieldmap file!" << std::endl;
  }
}


int main(){
  std::string fieldmap_interpolation_fn = "/home/fac_files/code/insertion_devices/fieldmaps/test_interpolation.txt";
  try{
    FieldMap fieldmap_interpolation(fieldmap_interpolation_fn.c_str());
    test_interpolation(fieldmap_interpolation);

  }
  catch(...){
    std::cout << "Can't open fieldmap file!" << std::endl;
  }

  InputParameters inputs;
  bool status;
  std::string input_filename = "/home/fac_files/code/insertion_devices/input_files/test_quadrupole.in";
  read_input_file(input_filename, status, inputs);
  if(status) generate_kickmap_and_test_kick(inputs);
}