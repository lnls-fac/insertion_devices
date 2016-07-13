#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <api.h>

static const double electron_rest_energy = 510998.92811;  // [eV]
static const double light_speed          = 299792458;     // [m/s]

void calc_brho(double energy, double& brho, double& beta){
  double gamma = energy / electron_rest_energy;
  beta  = std::sqrt(1.0 - 1.0 / (gamma * gamma));
  brho  = (beta * energy / light_speed);
}

void newton_lorentz_equation(double alpha, Vector3D<> r, Vector3D<> p,  Vector3D<> b, Vector3D<>& dr_ds, Vector3D<>& dp_ds){

  dr_ds.x = p.x;
  dr_ds.y = p.y;
  dr_ds.z = p.z;
  dp_ds.x = -alpha * (p.y * b.z - p.z * b.y);
  dp_ds.y = -alpha * (p.z * b.x - p.x * b.z);
  dp_ds.z = -alpha * (p.x * b.y - p.y * b.x);

}

void runge_kutta(InsertionDevice& insertiondevice, double brho, double beta, double zmax, double step, Mask mask, Vector3D<> r, Vector3D<> p, Vector3D<>& kicks, std::vector<std::vector<double> >& trajectory){

  double alpha = 1.0/brho/beta;
  bool inside = true;
  Vector3D<> b; Vector3D<> b1; Vector3D<> b2; Vector3D<> b3;
  Vector3D<> kr1; Vector3D<> kp1; Vector3D<> r1; Vector3D<> p1;
  Vector3D<> kr2; Vector3D<> kp2; Vector3D<> r2; Vector3D<> p2;
  Vector3D<> kr3; Vector3D<> kp3; Vector3D<> r3; Vector3D<> p3;
  Vector3D<> kr4; Vector3D<> kp4;

  if (!trajectory.empty()) { trajectory.clear(); }
  std::vector<double> particle_pos;
  particle_pos.push_back(r.x); particle_pos.push_back(r.y); particle_pos.push_back(r.z);
  particle_pos.push_back(p.x); particle_pos.push_back(p.y); particle_pos.push_back(p.z);
  trajectory.push_back(particle_pos);
  particle_pos.clear();

  while (r.z < zmax){

    inside = mask.is_inside(r); if(!inside) { p.x = p.y = p.z = NAN; break; }
    b = insertiondevice.field(r);
    newton_lorentz_equation(alpha, r, p, b, kr1, kp1);
    r1 = r + (step/2.0)* kr1;
    p1 = p + (step/2.0)* kp1;

    inside = mask.is_inside(r1); if(!inside) { p.x = p.y = p.z = NAN; break; }
    b1 = insertiondevice.field(r1);
    newton_lorentz_equation(alpha, r1, p1, b1, kr2, kp2);
    r2 = r + (step/2.0)* kr2;
    p2 = p + (step/2.0)* kp2;

    inside = mask.is_inside(r2); if(!inside) { p.x = p.y = p.z = NAN; break; }
    b2 = insertiondevice.field(r2);
    newton_lorentz_equation(alpha, r2, p2, b2, kr3, kp3);
    r3 = r + step* kr3;
    p3 = p + step* kp3;

    inside = mask.is_inside(r3); if(!inside) { p.x = p.y = p.z = NAN; break; }
    b3 = insertiondevice.field(r3);
    newton_lorentz_equation(alpha, r3, p3, b3, kr4, kp4);

    r = r + (step/6.0)*(kr1 + 2.0*kr2 + 2.0*kr3 + kr4);
    p = p + (step/6.0)*(kp1 + 2.0*kp2 + 2.0*kp3 + kp4);

    particle_pos.push_back(r.x); particle_pos.push_back(r.y); particle_pos.push_back(r.z);
    particle_pos.push_back(p.x); particle_pos.push_back(p.y); particle_pos.push_back(p.z);
    trajectory.push_back(particle_pos);
    particle_pos.clear();

  }

  kicks = p*(pow(brho, 2.0));

}

void runge_kutta(Vector3D<> (*function)(Vector3D<>), double brho, double beta, double zmax, double step, Mask mask, Vector3D<> r, Vector3D<> p, Vector3D<>& kicks, std::vector<std::vector<double> >& trajectory){
  InsertionDevice insertiondevice(function);
  runge_kutta(insertiondevice, brho, beta, zmax, step, mask, r, p, kicks, trajectory);
}

void _calc_kickmap(InsertionDevice& id, Grid grid, Mask mask, double energy, double rk_step, double z_min, double z_max, double physical_length, KickMap& kickmap, std::vector<std::vector<std::vector<double> > >& trajectories){

  double beta; double brho;
  calc_brho(energy, brho, beta);

  int count = 0;
  int size = grid.nx * grid.ny;
  std::vector<double> kick_x_vector;
  std::vector<double> kick_y_vector;
  Vector3D<> r(0.0, 0.0, z_min+1);
  Vector3D<> p(0.0, 0.0, 1.0);
  Vector3D<> kick;

  std::cout << std::endl;
  std::cout << "Calculating kickmap..." << std::endl;

  std::vector<std::vector<double> > kick_x;
	std::vector<std::vector<double> > kick_y;
  std::vector<std::vector<double> > trajectory;

  for(int i = 0; i < grid.ny; i+=1){
    kick_x_vector.clear();
    kick_y_vector.clear();

    for(int j =0; j < grid.nx; j+=1){
      r.x = grid.x[j];
      r.y = grid.y[i];
      runge_kutta(id, brho, beta, z_max, rk_step, mask, r, p, kick, trajectory);
      kick_x_vector.push_back(kick.x);
      kick_y_vector.push_back(kick.y);
      trajectories.push_back(trajectory);

      count += 1;
      if (count%10 == 0) {
        std::cout << std::setw(6) << std::setprecision(4) << std::setfill(' ') << 100.0*(double(count)/double(size)) << '%' << '\r' << std::flush;
      }

    }
    kick_x.push_back(kick_x_vector);
    kick_y.push_back(kick_y_vector);
  }

  KickMap kickm(physical_length, grid.x, grid.y, kick_x, kick_y);
  kickmap = kickm;

}

void _calc_kickmap(Vector3D<> (*function)(Vector3D<>), Grid grid, Mask mask, double energy, double rk_step, double z_min, double z_max, double physical_length, KickMap& kickmap, std::vector<std::vector<std::vector<double> > >& trajectories){
  InsertionDevice insertiondevice(function);
  _calc_kickmap(insertiondevice, grid, mask, energy, rk_step, z_min, z_max, physical_length, kickmap, trajectories);
}

void _write_fieldmap_file(InsertionDevice& insertiondevice, std::string filename, std::vector<double> x_vector, std::vector<double> y_vector, std::vector<double> z_vector){
  std::ofstream output_file(filename.c_str());

  if(!output_file){
    std::cout << "Can't open output file: " << filename <<  std::endl;
  } else {
    output_file << "Nome_do_Mapa:         " << "--" << std::endl;
    output_file << "Data_Hora:            " << "--" << std::endl;
    output_file << "Nome_do_Arquivo:      " << "--" << std::endl;
    output_file << "Numero_de_Imas:       " << "--" << std::endl;
    output_file << std::endl;
    output_file << "Nome_do_Ima:          " << "--" << std::endl;
    output_file << "Gap[mm]:              " << "--" << std::endl;
    output_file << "Gap_Controle[mm]:     " << "--" << std::endl;
    output_file << "Comprimento[mm]:      " << "--" << std::endl;
    output_file << "Corrente[A]:          " << "--" << std::endl;
    output_file << "Centro_Posicao_z[mm]: " << "--" << std::endl;
    output_file << "Centro_Posicao_x[mm]: " << "--" << std::endl;
    output_file << "Rotacao[graus]:       " << "--" << std::endl;
    output_file << std::endl;
    output_file << "X [mm]  Y[mm]  Z[mm] B x, B y, B z  [T]" << std::endl;
    output_file << "---------------------------------------------------------------------------------------------------------------" << std::endl;

    Vector3D<double> pos; Vector3D<double> b;
    for(int i = 0; i < z_vector.size(); i+=1){
      for (int j=0; j < y_vector.size(); j+=1){
        for(int k = 0; k < x_vector.size(); k+=1){
          pos.x = x_vector[k]; pos.y = y_vector[j]; pos.z = z_vector[i];
          b = insertiondevice.field(pos);
          output_file << std::scientific << std::showpos << pos.x*1000 << " ";
          output_file << std::scientific << std::showpos << pos.y*1000 << " ";
          output_file << std::scientific << std::showpos << pos.z*1000 << " ";
          output_file << std::scientific << std::showpos << b.x << " ";
          output_file << std::scientific << std::showpos << b.y << " ";
          output_file << std::scientific << std::showpos << b.z << std::endl;
        }
      }
    }

    std::cout << "Fieldmap saved in file: " << filename << std::endl << std::endl;
  }
}

void _write_fieldmap_file(Vector3D<> (*function)(Vector3D<>), std::string filename, std::vector<double> x_vector, std::vector<double> y_vector, std::vector<double> z_vector){
  InsertionDevice insertiondevice(function);
  _write_fieldmap_file(insertiondevice, filename, x_vector, y_vector, z_vector);
}

void _write_fieldmap_files(InsertionDevice& insertiondevice, std::string label, std::vector<double> x_vector, std::vector<double> y_vector, std::vector<double> z_vector){
  std::vector<double> y_value;
  std::ostringstream y_str;
  std::string filename_y;

  for(int i=0; i < y_vector.size(); i+=1){
    std::ostringstream ss;
    ss << (fabs(y_vector[i])*1000);
    std::string y_str(ss.str());

    if (y_vector[i] < 0){ filename_y = label  + "_yn" + y_str + ".txt"; }
    else if (y_vector[i] == 0){ filename_y = label + "_y0" + y_str + ".txt"; }
    else { filename_y = label + "_yp" + y_str + ".txt"; }

    y_value.push_back(y_vector[i]);
    _write_fieldmap_file(insertiondevice, filename_y, x_vector, y_value, z_vector);
    y_value.clear();
  }

}

void _write_fieldmap_files(Vector3D<> (*function)(Vector3D<>), std::string label, std::vector<double> x_vector, std::vector<double> y_vector, std::vector<double> z_vector){
  InsertionDevice insertiondevice(function);
  _write_fieldmap_files(insertiondevice, label, x_vector, y_vector, z_vector);
}


void _write_kickmap_file(std::string filename, double physical_length, std::vector<double>& x, std::vector<double>& y, std::vector<std::vector<double> >& kick_x, std::vector<std::vector<double> >& kick_y){

  time_t now = time(0); char* date = ctime(&now);

  std::ofstream output_file(filename.c_str());
  if(!output_file) {
    std::cout << "Can't open output file: " << filename << std::endl << std::endl;
    return;
  }

  int nx = x.size(); int ny = y.size();

  output_file << "# KICKMAP" << std::endl;
  output_file << "# Author: Luana N. P. Vilela @ LNLS, Date: " << date;
  output_file << "# ID Length [m]" << std::endl;
  output_file << physical_length << std::endl;
  output_file << "# Number of Horizontal Points" << std::endl;
  output_file << nx << std::endl;
  output_file << "# Number of Vertical Points" << std::endl;
  output_file << ny << std::endl;
  output_file << "# Horizontal KickTable in T2m2" << std::endl;
  output_file << "START" << std::endl;
  output_file << std::setw(14) << " ";

  for(int j =0; j < nx; j+=1){
      output_file << std::scientific << std::showpos << x[j] << " ";
  }
  output_file << std::endl;
  for(int i = 0; i < ny; i+=1){
    output_file << std::scientific << std::showpos << y[i] << " ";
    for(int j =0; j < nx; j+=1){
      if ( isnan(kick_x[i][j]) ) { output_file << std::setw(13) << std::setfill(' ') << kick_x[i][j] << " "; }
      else { output_file << std::scientific << std::showpos << kick_x[i][j] << " "; }
    }
    output_file << std::endl;
  }

  output_file << "# Vertical KickTable in T2m2" << std::endl;
  output_file << "START" << std::endl;
  output_file << std::setw(14) << " ";
  for(int j =0; j < nx; j+=1){
      output_file << std::scientific << std::showpos << x[j] << " ";
  }
  output_file << std::endl;
  for(int i = 0; i < ny; i+=1){
    output_file << std::scientific << std::showpos << y[i] << " ";
    for(int j =0; j < nx; j+=1){
      if ( isnan(kick_y[i][j]) ){ output_file << std::setw(13) << std::setfill(' ') << kick_y[i][j] << " "; }
      else { output_file << std::scientific << std::showpos << kick_y[i][j] << " "; }
    }
    output_file << std::endl;
  }

  std::cout << "Kickmap saved in file: " << std::endl;
  std::cout << filename << std::endl << std::endl;

}


void save_trajectories(std::string filename, std::vector<std::vector<std::vector<double> > >& trajectories){

  std::ofstream file(filename.c_str());
  if(!file) {
    std::cout << "Can't open output file: " << filename << std::endl << std::endl;
    return;
  }
  std::cout << std::endl << "Saving particle trajectories... " << std::endl;

  std::vector<std::vector<double> > trajectory;
  Vector3D<double> r;
  Vector3D<double> p;
  for (int i=0; i<trajectories.size(); i+=1){
    trajectory = trajectories[i];
    file << "START" << std::endl;
    for (int j=0; j<trajectory.size(); j+=1){
      r.x = trajectory[j][0]; r.y = trajectory[j][1]; r.z = trajectory[j][2];
      p.x = trajectory[j][3]; p.y = trajectory[j][3]; p.z = trajectory[j][5];
      file << r << " " << p << std::endl;
    }
  }

  std::cout << "Particle trajectories saved in file: " << std::endl;
  std::cout << filename << std::endl;

}

void save_trajectory(std::string filename, std::vector<std::vector<double> >& trajectory){

  std::ofstream file(filename.c_str());
  if(!file) {
    std::cout << "Can't open output file: " << filename << std::endl << std::endl;
    return;
  }
  std::cout << std::endl << "Saving particle trajectory... " << std::endl;

  Vector3D<double> r;
  Vector3D<double> p;
  for (int j=0; j<trajectory.size(); j+=1){
    r.x = trajectory[j][0]; r.y = trajectory[j][1]; r.z = trajectory[j][2];
    p.x = trajectory[j][3]; p.y = trajectory[j][3]; p.z = trajectory[j][5];
    file << r << " " << p << std::endl;
  }

  std::cout << "Particle trajectory saved in file: " << std::endl;
  std::cout << filename << std::endl;
}
