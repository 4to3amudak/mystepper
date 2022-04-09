from my_stepper import wiring_pi_setup, Stepper

wiring_pi_setup() #MANDATORY ONCE BEFORE Stepper creation 
#(ОБЯЗАТЕЛЬНО В НАЧАЛЕ ПРОГРАММЫ ПЕРЕД СОЗДАНИЕМ ОБЪЕКТА ШАГОВИКА)

stp = Stepper()
#Stepper default (шаговик по умолчанию)
stp.rotate_full_rel()
#one stepper revolution (один оборот)
print(stp.get_total_fact_angle())
#prints angle after movement (написать полный угол после движения)
