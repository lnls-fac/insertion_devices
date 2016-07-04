# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.11
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_insertion_devices', [dirname(__file__)])
        except ImportError:
            import _insertion_devices
            return _insertion_devices
        if fp is not None:
            try:
                _mod = imp.load_module('_insertion_devices', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _insertion_devices = swig_import_helper()
    del swig_import_helper
else:
    import _insertion_devices
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


class SwigPyIterator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SwigPyIterator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SwigPyIterator, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _insertion_devices.delete_SwigPyIterator
    __del__ = lambda self : None;
    def value(self): return _insertion_devices.SwigPyIterator_value(self)
    def incr(self, n=1): return _insertion_devices.SwigPyIterator_incr(self, n)
    def decr(self, n=1): return _insertion_devices.SwigPyIterator_decr(self, n)
    def distance(self, *args): return _insertion_devices.SwigPyIterator_distance(self, *args)
    def equal(self, *args): return _insertion_devices.SwigPyIterator_equal(self, *args)
    def copy(self): return _insertion_devices.SwigPyIterator_copy(self)
    def next(self): return _insertion_devices.SwigPyIterator_next(self)
    def __next__(self): return _insertion_devices.SwigPyIterator___next__(self)
    def previous(self): return _insertion_devices.SwigPyIterator_previous(self)
    def advance(self, *args): return _insertion_devices.SwigPyIterator_advance(self, *args)
    def __eq__(self, *args): return _insertion_devices.SwigPyIterator___eq__(self, *args)
    def __ne__(self, *args): return _insertion_devices.SwigPyIterator___ne__(self, *args)
    def __iadd__(self, *args): return _insertion_devices.SwigPyIterator___iadd__(self, *args)
    def __isub__(self, *args): return _insertion_devices.SwigPyIterator___isub__(self, *args)
    def __add__(self, *args): return _insertion_devices.SwigPyIterator___add__(self, *args)
    def __sub__(self, *args): return _insertion_devices.SwigPyIterator___sub__(self, *args)
    def __iter__(self): return self
SwigPyIterator_swigregister = _insertion_devices.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)

class GridException(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, GridException, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, GridException, name)
    __repr__ = _swig_repr
    inconsistent_dimensions = _insertion_devices.GridException_inconsistent_dimensions
    def __init__(self): 
        this = _insertion_devices.new_GridException()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _insertion_devices.delete_GridException
    __del__ = lambda self : None;
GridException_swigregister = _insertion_devices.GridException_swigregister
GridException_swigregister(GridException)

class MaskException(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, MaskException, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, MaskException, name)
    __repr__ = _swig_repr
    file_not_found = _insertion_devices.MaskException_file_not_found
    undefined_shape = _insertion_devices.MaskException_undefined_shape
    def __init__(self): 
        this = _insertion_devices.new_MaskException()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _insertion_devices.delete_MaskException
    __del__ = lambda self : None;
MaskException_swigregister = _insertion_devices.MaskException_swigregister
MaskException_swigregister(MaskException)

class FieldMapException(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, FieldMapException, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, FieldMapException, name)
    __repr__ = _swig_repr
    inconsistent_dimensions = _insertion_devices.FieldMapException_inconsistent_dimensions
    file_not_found = _insertion_devices.FieldMapException_file_not_found
    def __init__(self): 
        this = _insertion_devices.new_FieldMapException()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _insertion_devices.delete_FieldMapException
    __del__ = lambda self : None;
FieldMapException_swigregister = _insertion_devices.FieldMapException_swigregister
FieldMapException_swigregister(FieldMapException)

class Grid(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Grid, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Grid, name)
    __repr__ = _swig_repr
    __swig_setmethods__["nx"] = _insertion_devices.Grid_nx_set
    __swig_getmethods__["nx"] = _insertion_devices.Grid_nx_get
    if _newclass:nx = _swig_property(_insertion_devices.Grid_nx_get, _insertion_devices.Grid_nx_set)
    __swig_setmethods__["ny"] = _insertion_devices.Grid_ny_set
    __swig_getmethods__["ny"] = _insertion_devices.Grid_ny_get
    if _newclass:ny = _swig_property(_insertion_devices.Grid_ny_get, _insertion_devices.Grid_ny_set)
    __swig_setmethods__["x"] = _insertion_devices.Grid_x_set
    __swig_getmethods__["x"] = _insertion_devices.Grid_x_get
    if _newclass:x = _swig_property(_insertion_devices.Grid_x_get, _insertion_devices.Grid_x_set)
    __swig_setmethods__["y"] = _insertion_devices.Grid_y_set
    __swig_getmethods__["y"] = _insertion_devices.Grid_y_get
    if _newclass:y = _swig_property(_insertion_devices.Grid_y_get, _insertion_devices.Grid_y_set)
    def __init__(self, *args): 
        this = _insertion_devices.new_Grid(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _insertion_devices.delete_Grid
    __del__ = lambda self : None;
Grid_swigregister = _insertion_devices.Grid_swigregister
Grid_swigregister(Grid)

class Mask(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Mask, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Mask, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _insertion_devices.new_Mask(*args)
        try: self.this.append(this)
        except: self.this = this
    def load(self, *args): return _insertion_devices.Mask_load(self, *args)
    def is_inside(self, *args): return _insertion_devices.Mask_is_inside(self, *args)
    __swig_destroy__ = _insertion_devices.delete_Mask
    __del__ = lambda self : None;
Mask_swigregister = _insertion_devices.Mask_swigregister
Mask_swigregister(Mask)

class FieldMap(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, FieldMap, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, FieldMap, name)
    __repr__ = _swig_repr
    __swig_setmethods__["id"] = _insertion_devices.FieldMap_id_set
    __swig_getmethods__["id"] = _insertion_devices.FieldMap_id_get
    if _newclass:id = _swig_property(_insertion_devices.FieldMap_id_get, _insertion_devices.FieldMap_id_set)
    __swig_setmethods__["nx"] = _insertion_devices.FieldMap_nx_set
    __swig_getmethods__["nx"] = _insertion_devices.FieldMap_nx_get
    if _newclass:nx = _swig_property(_insertion_devices.FieldMap_nx_get, _insertion_devices.FieldMap_nx_set)
    __swig_setmethods__["nz"] = _insertion_devices.FieldMap_nz_set
    __swig_getmethods__["nz"] = _insertion_devices.FieldMap_nz_get
    if _newclass:nz = _swig_property(_insertion_devices.FieldMap_nz_get, _insertion_devices.FieldMap_nz_set)
    __swig_setmethods__["x_min"] = _insertion_devices.FieldMap_x_min_set
    __swig_getmethods__["x_min"] = _insertion_devices.FieldMap_x_min_get
    if _newclass:x_min = _swig_property(_insertion_devices.FieldMap_x_min_get, _insertion_devices.FieldMap_x_min_set)
    __swig_setmethods__["dx"] = _insertion_devices.FieldMap_dx_set
    __swig_getmethods__["dx"] = _insertion_devices.FieldMap_dx_get
    if _newclass:dx = _swig_property(_insertion_devices.FieldMap_dx_get, _insertion_devices.FieldMap_dx_set)
    __swig_setmethods__["x_max"] = _insertion_devices.FieldMap_x_max_set
    __swig_getmethods__["x_max"] = _insertion_devices.FieldMap_x_max_get
    if _newclass:x_max = _swig_property(_insertion_devices.FieldMap_x_max_get, _insertion_devices.FieldMap_x_max_set)
    __swig_setmethods__["z_min"] = _insertion_devices.FieldMap_z_min_set
    __swig_getmethods__["z_min"] = _insertion_devices.FieldMap_z_min_get
    if _newclass:z_min = _swig_property(_insertion_devices.FieldMap_z_min_get, _insertion_devices.FieldMap_z_min_set)
    __swig_setmethods__["dz"] = _insertion_devices.FieldMap_dz_set
    __swig_getmethods__["dz"] = _insertion_devices.FieldMap_dz_get
    if _newclass:dz = _swig_property(_insertion_devices.FieldMap_dz_get, _insertion_devices.FieldMap_dz_set)
    __swig_setmethods__["z_max"] = _insertion_devices.FieldMap_z_max_set
    __swig_getmethods__["z_max"] = _insertion_devices.FieldMap_z_max_get
    if _newclass:z_max = _swig_property(_insertion_devices.FieldMap_z_max_get, _insertion_devices.FieldMap_z_max_set)
    __swig_setmethods__["y"] = _insertion_devices.FieldMap_y_set
    __swig_getmethods__["y"] = _insertion_devices.FieldMap_y_get
    if _newclass:y = _swig_property(_insertion_devices.FieldMap_y_get, _insertion_devices.FieldMap_y_set)
    __swig_setmethods__["physical_length"] = _insertion_devices.FieldMap_physical_length_set
    __swig_getmethods__["physical_length"] = _insertion_devices.FieldMap_physical_length_get
    if _newclass:physical_length = _swig_property(_insertion_devices.FieldMap_physical_length_get, _insertion_devices.FieldMap_physical_length_set)
    __swig_setmethods__["x_grid"] = _insertion_devices.FieldMap_x_grid_set
    __swig_getmethods__["x_grid"] = _insertion_devices.FieldMap_x_grid_get
    if _newclass:x_grid = _swig_property(_insertion_devices.FieldMap_x_grid_get, _insertion_devices.FieldMap_x_grid_set)
    __swig_setmethods__["z_grid"] = _insertion_devices.FieldMap_z_grid_set
    __swig_getmethods__["z_grid"] = _insertion_devices.FieldMap_z_grid_get
    if _newclass:z_grid = _swig_property(_insertion_devices.FieldMap_z_grid_get, _insertion_devices.FieldMap_z_grid_set)
    __swig_setmethods__["data"] = _insertion_devices.FieldMap_data_set
    __swig_getmethods__["data"] = _insertion_devices.FieldMap_data_get
    if _newclass:data = _swig_property(_insertion_devices.FieldMap_data_get, _insertion_devices.FieldMap_data_set)
    __swig_setmethods__["fname"] = _insertion_devices.FieldMap_fname_set
    __swig_getmethods__["fname"] = _insertion_devices.FieldMap_fname_get
    if _newclass:fname = _swig_property(_insertion_devices.FieldMap_fname_get, _insertion_devices.FieldMap_fname_set)
    def __init__(self, *args): 
        this = _insertion_devices.new_FieldMap(*args)
        try: self.this.append(this)
        except: self.this = this
    def getid(self): return _insertion_devices.FieldMap_getid(self)
    def field(self, *args): return _insertion_devices.FieldMap_field(self, *args)
    def delete_data(self): return _insertion_devices.FieldMap_delete_data(self)
    def change_y_sign(self): return _insertion_devices.FieldMap_change_y_sign(self)
    __swig_destroy__ = _insertion_devices.delete_FieldMap
    __del__ = lambda self : None;
FieldMap_swigregister = _insertion_devices.FieldMap_swigregister
FieldMap_swigregister(FieldMap)

class FieldMapContainer(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, FieldMapContainer, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, FieldMapContainer, name)
    __repr__ = _swig_repr
    __swig_setmethods__["nr_fieldmaps"] = _insertion_devices.FieldMapContainer_nr_fieldmaps_set
    __swig_getmethods__["nr_fieldmaps"] = _insertion_devices.FieldMapContainer_nr_fieldmaps_get
    if _newclass:nr_fieldmaps = _swig_property(_insertion_devices.FieldMapContainer_nr_fieldmaps_get, _insertion_devices.FieldMapContainer_nr_fieldmaps_set)
    __swig_setmethods__["z_min"] = _insertion_devices.FieldMapContainer_z_min_set
    __swig_getmethods__["z_min"] = _insertion_devices.FieldMapContainer_z_min_get
    if _newclass:z_min = _swig_property(_insertion_devices.FieldMapContainer_z_min_get, _insertion_devices.FieldMapContainer_z_min_set)
    __swig_setmethods__["z_max"] = _insertion_devices.FieldMapContainer_z_max_set
    __swig_getmethods__["z_max"] = _insertion_devices.FieldMapContainer_z_max_get
    if _newclass:z_max = _swig_property(_insertion_devices.FieldMapContainer_z_max_get, _insertion_devices.FieldMapContainer_z_max_set)
    __swig_setmethods__["physical_length"] = _insertion_devices.FieldMapContainer_physical_length_set
    __swig_getmethods__["physical_length"] = _insertion_devices.FieldMapContainer_physical_length_get
    if _newclass:physical_length = _swig_property(_insertion_devices.FieldMapContainer_physical_length_get, _insertion_devices.FieldMapContainer_physical_length_set)
    def __init__(self, *args): 
        this = _insertion_devices.new_FieldMapContainer(*args)
        try: self.this.append(this)
        except: self.this = this
    def field(self, *args): return _insertion_devices.FieldMapContainer_field(self, *args)
    __swig_destroy__ = _insertion_devices.delete_FieldMapContainer
    __del__ = lambda self : None;
FieldMapContainer_swigregister = _insertion_devices.FieldMapContainer_swigregister
FieldMapContainer_swigregister(FieldMapContainer)

class KickMap(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KickMap, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KickMap, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _insertion_devices.new_KickMap(*args)
        try: self.this.append(this)
        except: self.this = this
    def write_kickmap(self, *args): return _insertion_devices.KickMap_write_kickmap(self, *args)
    __swig_destroy__ = _insertion_devices.delete_KickMap
    __del__ = lambda self : None;
KickMap_swigregister = _insertion_devices.KickMap_swigregister
KickMap_swigregister(KickMap)


def runge_kutta(*args):
  return _insertion_devices.runge_kutta(*args)
runge_kutta = _insertion_devices.runge_kutta
class CppStringVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CppStringVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CppStringVector, name)
    __repr__ = _swig_repr
    def iterator(self): return _insertion_devices.CppStringVector_iterator(self)
    def __iter__(self): return self.iterator()
    def __nonzero__(self): return _insertion_devices.CppStringVector___nonzero__(self)
    def __bool__(self): return _insertion_devices.CppStringVector___bool__(self)
    def __len__(self): return _insertion_devices.CppStringVector___len__(self)
    def pop(self): return _insertion_devices.CppStringVector_pop(self)
    def __getslice__(self, *args): return _insertion_devices.CppStringVector___getslice__(self, *args)
    def __setslice__(self, *args): return _insertion_devices.CppStringVector___setslice__(self, *args)
    def __delslice__(self, *args): return _insertion_devices.CppStringVector___delslice__(self, *args)
    def __delitem__(self, *args): return _insertion_devices.CppStringVector___delitem__(self, *args)
    def __getitem__(self, *args): return _insertion_devices.CppStringVector___getitem__(self, *args)
    def __setitem__(self, *args): return _insertion_devices.CppStringVector___setitem__(self, *args)
    def append(self, *args): return _insertion_devices.CppStringVector_append(self, *args)
    def empty(self): return _insertion_devices.CppStringVector_empty(self)
    def size(self): return _insertion_devices.CppStringVector_size(self)
    def clear(self): return _insertion_devices.CppStringVector_clear(self)
    def swap(self, *args): return _insertion_devices.CppStringVector_swap(self, *args)
    def get_allocator(self): return _insertion_devices.CppStringVector_get_allocator(self)
    def begin(self): return _insertion_devices.CppStringVector_begin(self)
    def end(self): return _insertion_devices.CppStringVector_end(self)
    def rbegin(self): return _insertion_devices.CppStringVector_rbegin(self)
    def rend(self): return _insertion_devices.CppStringVector_rend(self)
    def pop_back(self): return _insertion_devices.CppStringVector_pop_back(self)
    def erase(self, *args): return _insertion_devices.CppStringVector_erase(self, *args)
    def __init__(self, *args): 
        this = _insertion_devices.new_CppStringVector(*args)
        try: self.this.append(this)
        except: self.this = this
    def push_back(self, *args): return _insertion_devices.CppStringVector_push_back(self, *args)
    def front(self): return _insertion_devices.CppStringVector_front(self)
    def back(self): return _insertion_devices.CppStringVector_back(self)
    def assign(self, *args): return _insertion_devices.CppStringVector_assign(self, *args)
    def resize(self, *args): return _insertion_devices.CppStringVector_resize(self, *args)
    def insert(self, *args): return _insertion_devices.CppStringVector_insert(self, *args)
    def reserve(self, *args): return _insertion_devices.CppStringVector_reserve(self, *args)
    def capacity(self): return _insertion_devices.CppStringVector_capacity(self)
    __swig_destroy__ = _insertion_devices.delete_CppStringVector
    __del__ = lambda self : None;
CppStringVector_swigregister = _insertion_devices.CppStringVector_swigregister
CppStringVector_swigregister(CppStringVector)

class CppDoubleVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CppDoubleVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CppDoubleVector, name)
    __repr__ = _swig_repr
    def iterator(self): return _insertion_devices.CppDoubleVector_iterator(self)
    def __iter__(self): return self.iterator()
    def __nonzero__(self): return _insertion_devices.CppDoubleVector___nonzero__(self)
    def __bool__(self): return _insertion_devices.CppDoubleVector___bool__(self)
    def __len__(self): return _insertion_devices.CppDoubleVector___len__(self)
    def pop(self): return _insertion_devices.CppDoubleVector_pop(self)
    def __getslice__(self, *args): return _insertion_devices.CppDoubleVector___getslice__(self, *args)
    def __setslice__(self, *args): return _insertion_devices.CppDoubleVector___setslice__(self, *args)
    def __delslice__(self, *args): return _insertion_devices.CppDoubleVector___delslice__(self, *args)
    def __delitem__(self, *args): return _insertion_devices.CppDoubleVector___delitem__(self, *args)
    def __getitem__(self, *args): return _insertion_devices.CppDoubleVector___getitem__(self, *args)
    def __setitem__(self, *args): return _insertion_devices.CppDoubleVector___setitem__(self, *args)
    def append(self, *args): return _insertion_devices.CppDoubleVector_append(self, *args)
    def empty(self): return _insertion_devices.CppDoubleVector_empty(self)
    def size(self): return _insertion_devices.CppDoubleVector_size(self)
    def clear(self): return _insertion_devices.CppDoubleVector_clear(self)
    def swap(self, *args): return _insertion_devices.CppDoubleVector_swap(self, *args)
    def get_allocator(self): return _insertion_devices.CppDoubleVector_get_allocator(self)
    def begin(self): return _insertion_devices.CppDoubleVector_begin(self)
    def end(self): return _insertion_devices.CppDoubleVector_end(self)
    def rbegin(self): return _insertion_devices.CppDoubleVector_rbegin(self)
    def rend(self): return _insertion_devices.CppDoubleVector_rend(self)
    def pop_back(self): return _insertion_devices.CppDoubleVector_pop_back(self)
    def erase(self, *args): return _insertion_devices.CppDoubleVector_erase(self, *args)
    def __init__(self, *args): 
        this = _insertion_devices.new_CppDoubleVector(*args)
        try: self.this.append(this)
        except: self.this = this
    def push_back(self, *args): return _insertion_devices.CppDoubleVector_push_back(self, *args)
    def front(self): return _insertion_devices.CppDoubleVector_front(self)
    def back(self): return _insertion_devices.CppDoubleVector_back(self)
    def assign(self, *args): return _insertion_devices.CppDoubleVector_assign(self, *args)
    def resize(self, *args): return _insertion_devices.CppDoubleVector_resize(self, *args)
    def insert(self, *args): return _insertion_devices.CppDoubleVector_insert(self, *args)
    def reserve(self, *args): return _insertion_devices.CppDoubleVector_reserve(self, *args)
    def capacity(self): return _insertion_devices.CppDoubleVector_capacity(self)
    __swig_destroy__ = _insertion_devices.delete_CppDoubleVector
    __del__ = lambda self : None;
CppDoubleVector_swigregister = _insertion_devices.CppDoubleVector_swigregister
CppDoubleVector_swigregister(CppDoubleVector)

# This file is compatible with both classic and new-style classes.


