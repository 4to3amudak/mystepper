import ctypes as ct

lib = ct.cdll.LoadLibrary('./libmystepper.dll')
#Параметры аргументов функций библиотеки
lib.st_init.argtypes = [ct.c_long, ct.c_int, ct.c_int, \
    ct.c_double, ct.c_double, ct.c_double, ct.c_double]
lib.st_init.restype = ct.c_void_p
lib.st_destroy.argtypes = [ct.c_void_p]
lib.st_destroy.restype = ct.c_void_p
lib.st_get_step_per_rev.argtypes = [ct.c_void_p]
lib.st_get_step_per_rev.restype = ct.c_int
lib.st_get_handle_ratio.argtypes = [ct.c_void_p]
lib.st_get_handle_ratio.restype = ct.c_double
lib.st_get_accel.argtypes = [ct.c_void_p]
lib.st_get_accel.restype = ct.c_double
lib.st_get_jerk.argtypes = [ct.c_void_p]
lib.st_get_jerk.restype = ct.c_double
lib.st_get_default_speed.argtypes = [ct.c_void_p]
lib.st_get_default_speed.restype = ct.c_double
lib.st_get_st_pin.argtypes = [ct.c_void_p]
lib.st_get_st_pin.restype = ct.c_int
lib.st_get_dir_pin.argtypes = [ct.c_void_p]
lib.st_get_dir_pin.restype = ct.c_int
lib.st_get_user_angle.argtypes = [ct.c_void_p]
lib.st_get_user_angle.restype = ct.c_double
lib.st_get_fact_angle.argtypes = [ct.c_void_p]
lib.st_get_fact_angle.restype = ct.c_double
lib.st_get_full_revs.argtypes = [ct.c_void_p]
lib.st_get_full_revs.restype = ct.c_longlong
lib.st_clear_dists.argtypes = [ct.c_void_p]
lib.st_clear_dists.restype = ct.c_void_p
lib.st_set_step_per_rev.argtypes = [ct.c_void_p, ct.c_int]
lib.st_set_step_per_rev.restype = ct.c_void_p
lib.st_set_handle_ratio.argtypes = [ct.c_void_p, ct.c_double]
lib.st_set_handle_ratio.restype = ct.c_void_p
lib.st_set_speed_default.argtypes = [ct.c_void_p, ct.c_double]
lib.st_set_speed_default.restype = ct.c_void_p
lib.st_set_accel.argtypes = [ct.c_void_p, ct.c_double]
lib.st_set_accel.restype = ct.c_void_p
lib.st_set_jerk.argtypes = [ct.c_void_p, ct.c_double]
lib.st_set_jerk.restype = ct.c_void_p
lib.st_rotate_rel_sp.argtypes = [ct.c_void_p, \
    ct.c_double, ct.c_double]
lib.st_rotate_rel_sp.restype = ct.c_void_p
lib.st_rotate_to_ang_sp.argtypes = [ct.c_void_p, \
    ct.c_double, ct.c_double]
lib.st_rotate_to_ang_sp.restype = ct.c_void_p
lib.st_rotate_full_rel_sp.argtypes = [ct.c_void_p, \
    ct.c_int, ct.c_double]
lib.st_rotate_full_rel_sp.restype = ct.c_void_p
lib.st_rotate_rel.argtypes = [ct.c_void_p, ct.c_double]
lib.st_rotate_rel.restype = ct.c_void_p
lib.st_rotate_to_ang.argtypes = [ct.c_void_p, ct.c_double]
lib.st_rotate_to_ang.restype = ct.c_void_p
lib.st_rotate_full_rel.argtypes = [ct.c_void_p, ct.c_int]
lib.st_rotate_full_rel.restype = ct.c_void_p


def wiring_pi_setup():
	print("#wiringPi is set up\n")
#MANDATORY ONCE BEFORE Stepper creation 
#(ОБЯЗАТЕЛЬНО В НАЧАЛЕ ПРОГРАММЫ ПЕРЕД СОЗДАНИЕМ ОБЪЕКТА ШАГОВИКА)

#Класс для работы с шаговым двигателем
class Stepper:
    def __init__(self, spr=6400, step_p=3, dir_p=4, \
        speed_default=90.0, acceleration=900.0, \
        jerk=3.0, handle=1.0):
        self.obj = lib.st_init(spr, step_p, dir_p, \
            speed_default, acceleration, jerk, handle)
    #Конструкстор, параметры:
    #Кол-во шагов на оборот, номера пинов шагов и направления,
    #стандартная скорость, ускорение, начальная скорость (рывок)
    #коэф. редукторной передачи (1.0 - если нет)
    #Constructor, args:
    #Step number per revolution, step and dir pin numbers,
    #default speed, acceleration, initial speed (jerk),
    #gearbox ratio, 1.0 if gearbox is not present

    def __del__(self):
        lib.st_destroy(self.obj)
    #Деструктор
    #Destructor

    def get_step_per_rev(self):
        return lib.st_get_step_per_rev(self.obj)
    #Получить кол-во шагов на оборот
    #Get step number per revolution

    def get_handle_ratio(self):
        return lib.st_get_handle_ratio(self.obj)
    #Получить коэф. редукторной передачи
    #Get gearbox ratio

    def get_accel(self):
        return lib.st_get_accel(self.obj)
    #Получить ускорение
    #Get acceleration

    def get_jerk(self):
        return lib.st_get_jerk(self.obj)
    #Получить начальную скорость (рывок)
    #Get initial speed (jerk)

    def get_default_speed(self):
        return lib.st_get_default_speed(self.obj)
    #Получить стандартную скорость
    #Get default speed

    def get_st_pin(self):
        return lib.st_get_st_pin(self.obj)
    #Получить номер пина шагов
    #Get step pin number

    def get_dir_pin(self):
        return lib.st_get_dir_pin(self.obj)
    #Получить номер пина направления
    #Get dir pin number

    def get_user_angle(self):
        return lib.st_get_user_angle(self.obj)
    #Получить заданный угол оси
    #Get defined angle

    def get_fact_angle(self):
        return lib.st_get_fact_angle(self.obj)
    #Получить фактичесткий угол оси
    #Get real angle

    def get_full_revs(self):
        return lib.st_get_full_revs(self.obj)
    #Получить абсолютное кол-во оборотов от начальной позиции
    #Get absolute amount of revolutions relatively to initial coords.

    def get_total_user_angle(self):
        return lib.st_get_user_angle(self.obj) + \
            (lib.st_get_full_revs(self.obj) * 360.0)
    #Получить заданный угол от начальной позиции
    #Get defined angle relatively to initial coords.

    def get_total_fact_angle(self):
        return lib.st_get_fact_angle(self.obj) + \
            (lib.st_get_full_revs(self.obj) * 360.0)
    #Получить фактичесткий угол оси от начальной позиции
    #Get real angle relatively to initial coords.

    def clear_dists(self):
        lib.st_clear_dists(self.obj)
    #Сброс пройденных расстояний
    #Reset coords

    def set_step_per_rev(self, val):
        lib.st_set_step_per_rev(self.obj, val)
    #Установить кол-во шагов на оборот
    #Set step number per revolution

    def set_handle_ratio(self, val):
        lib.st_set_handle_ratio(self.obj, val)
    #Установить коэф. редукторной передачи
    #Set gearbox ratio

    def set_speed_default(self, val):
        lib.st_set_speed_default(self.obj, val)
    #Установить стандартную скорость
    #Set default speed

    def set_accel(self, val):
        lib.st_set_accel(self.obj, val)
    #Установить ускорение
    #Set acceleration

    def set_jerk(self, val):
        lib.st_set_jerk(self.obj, val)
    #Установить начальную скорость (рывок)
    #Set initial speed (jerk)

    def rotate_rel(self, ang, speed):
        lib.st_rotate_rel_sp(self.obj, ang, speed)
    #Повернуть на угол
    #rotate for angle

    def rotate_to_ang(self, ang, speed):
        lib.st_rotate_to_ang_sp(self.obj, ang, speed)
    #Повернуть к указанному углу вала
    #rotate for absolute shaft angle

    def rotate_full_rel(self, revs, speed):
        lib.st_rotate_full_rel_sp(self.obj, revs, speed)
    #Повернуть на число оборотов
    #rotate for full revolutions

    def rotate_rel(self, ang):
        lib.st_rotate_rel(self.obj, ang)

    def rotate_to_ang(self, ang):
        lib.st_rotate_to_ang(self.obj, ang)

    def rotate_full_rel(self, revs=1):
        lib.st_rotate_full_rel(self.obj, revs)
