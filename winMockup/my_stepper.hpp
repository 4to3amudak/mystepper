#pragma once

/*
wiringPiSetup()
MANDATORY ONCE BEFORE Stepper creation 
(ОБЯЗАТЕЛЬНО В НАЧАЛЕ ПРОГРАММЫ ПЕРЕД СОЗДАНИЕМ ОБЪЕКТА ШАГОВИКА)
*/


class Stepper
{
protected:
    double m_angle, u_angle;
    long long rev_cnt;
    int step_per_rev;
    double handle_ratio;
    int st_pin, dir_pin;
    double speed_default;
    double accel;
    double jerk;
    void _rotate_routine(long long steps, double speed);
    void _make_step(unsigned int us);
    void _reduce_angle();
public:
    Stepper(long spr, int st_p, int dir_p,
        double sd = 30, double a = 100,
        double j = 1, double hr = 1);
    /*
    #Конструкстор, параметры:
    #Кол-во шагов на оборот, номера пинов шагов и направления,
    #стандартная скорость, ускорение, начальная скорость (рывок)
    #коэф. редукторной передачи (1.0 - если нет)
    #Constructor, args:
    #Step number per revolution, step and dir pin numbers,
    #default speed, acceleration, initial speed (jerk),
    #gearbox ratio, 1.0 if gearbox is not present
    */

    int get_step_per_rev()
    {
        return step_per_rev;
    }
    /*
    #Получить кол-во шагов на оборот
    #Get step number per revolution
    */

    double get_handle_ratio()
    {
        return handle_ratio;
    }
    /*
    #Получить коэф. редукторной передачи
    #Get gearbox ratio
    */

    double get_accel()
    {
        return accel;
    }
    /*
    #Получить ускорение
    #Get acceleration
    */

    double get_jerk()
    {
        return jerk;
    }
    /*
    #Получить начальную скорость (рывок)
    #Get initial speed (jerk)
    */

    double get_default_speed()
    {
        return speed_default;
    }
    /*
    #Получить стандартную скорость
    #Get default speed
    */

    int get_st_pin()
    {
        return st_pin;
    }
    /*
    #Получить номер пина шагов
    #Get step pin number
    */

    int get_dir_pin()
    {
        return dir_pin;
    }
    /*
    #Получить номер пина направления
    #Get dir pin number
    */

    double get_user_angle()
    {
        return m_angle;
    }
    /*
    #Получить заданный угол оси
    #Get defined angle
    */

    double get_fact_angle()
    {
        return u_angle;
    }
    /*
    #Получить фактичесткий угол оси
    #Get real angle
    */

    long long get_full_revs()
    {
        return rev_cnt;
    }
    /*
    #Получить абсолютное кол-во оборотов от начальной позиции
    #Get absolute amount of revolutions relatively to initial coords.
    */

    double get_total_user_angle()
    {
        return m_angle + rev_cnt * 360.0;
    }
    /*
    #Получить заданный угол от начальной позиции
    #Get defined angle relatively to initial coords.
    */

    double get_total_fact_angle()
    {
        return u_angle + rev_cnt * 360.0;
    }
    /*
    #Получить фактичесткий угол оси от начальной позиции
    #Get real angle relatively to initial coords.
    */

    void clear_dists()
    {
        u_angle = m_angle = 0.0;
        rev_cnt = 0;
    }
    /*
    #Сброс пройденных расстояний
    #Reset coords
    */

    void set_step_per_rev(int s)
    {
        step_per_rev = s;
    }
    /*
    #Установить кол-во шагов на оборот
    #Set step number per revolution
    */

    void set_handle_ratio(double h)
    {
        handle_ratio = h;
    }
    /*
    #Установить коэф. редукторной передачи
    #Set gearbox ratio
    */

    void set_speed_default(double s)
    {
        speed_default = s;
    }
    /*
    #Установить стандартную скорость
    #Set default speed
    */

    void set_accel(double a)
    {
        accel = a;
    }
    /*
    #Установить ускорение
    #Set acceleration
    */

    void set_jerk(double j)
    {
        jerk = j;
    }
    /*
    #Установить начальную скорость (рывок)
    #Set initial speed (jerk)
    */

    void rotate_rel(double angle, double speed);
    void rotate_rel(double angle)
    {
        rotate_rel(angle, speed_default);
    }
    /*
    #Повернуть на угол
    #rotate for angle
    */

    void rotate_to_ang(double angle, double speed);
    void rotate_to_ang(double angle)
    {
        rotate_to_ang(angle, speed_default);
    }
    /*
    #Повернуть к указанному углу вала
    #rotate for absolute shaft angle
    */

    void rotate_full_rel(int revs, double speed);
    void rotate_full_rel(int revs = 1)
    {
        rotate_full_rel(revs, speed_default);
    }
    /*
    #Повернуть на число оборотов
    #rotate for full revolutions
    */
};

//Адаптер на сишные наименования функций
//For using with external C (non cpp) compliant tools
extern "C"  {
    Stepper* st_init(long spr,
        int st_p, int dir_p,
        double sd, double a,
        double j, double hr)
    {
        return new Stepper(spr, st_p, dir_p, sd, a, j, hr);
    }
    void st_destroy(Stepper* st)
    {
        delete st;
    }
    int st_get_step_per_rev(Stepper* st)
    {
        return st->get_step_per_rev();
    }
    double st_get_handle_ratio(Stepper* st)
    {
        return st->get_handle_ratio();
    }
    double st_get_accel(Stepper* st)
    {
        return st->get_accel();
    }
    double st_get_jerk(Stepper* st)
    {
        return st->get_jerk();
    }
    double st_get_default_speed(Stepper* st)
    {
        return st->get_default_speed();
    }
    int st_get_st_pin(Stepper* st)
    {
        return st->get_st_pin();
    }
    int st_get_dir_pin(Stepper* st)
    {
        return st->get_dir_pin();
    }
    double st_get_user_angle(Stepper* st)
    {
        return st->get_user_angle();
    }
    double st_get_fact_angle(Stepper* st)
    {
        return st->get_fact_angle();
    }
    long long st_get_full_revs(Stepper* st)
    {
        return st->get_full_revs();
    }
    void st_clear_dists(Stepper* st)
    {
        st->clear_dists();
    }
    void st_set_step_per_rev(Stepper* st, int s)
    {
        st->set_step_per_rev(s);
    }
    void st_set_handle_ratio(Stepper* st, double h)
    {
        st->set_handle_ratio(h);
    }
    void st_set_speed_default(Stepper* st, double s)
    {
        st->set_speed_default(s);
    }
    void st_set_accel(Stepper* st, double a)
    {
        st->set_accel(a);
    }
    void st_set_jerk(Stepper* st, double j)
    {
        st->set_jerk(j);
    }
    void st_rotate_rel_sp(Stepper* st, double angle, double speed)
    {
        st->rotate_rel(angle, speed);
    }
    void st_rotate_to_ang_sp(Stepper* st, double angle, double speed)
    {
        st->rotate_to_ang(angle, speed);
    }
    void st_rotate_full_rel_sp(Stepper* st, int revs, double speed)
    {
        st->rotate_full_rel(revs, speed);
    }
    void st_rotate_rel(Stepper* st, double angle)
    {
        st->rotate_rel(angle);
    }
    void st_rotate_to_ang(Stepper* st, double angle)
    {
        st->rotate_to_ang(angle);
    }
    void st_rotate_full_rel(Stepper* st, int revs)
    {
        st->rotate_full_rel(revs);
    }
}
