import sys 
import os
sys.path.append(os.path.join(os.path.dirname(__file__), "../bin"))
import example as m
from example import Pet
from example import ekf
from example import VOMeasurement, WheelMeasurement, create_vomeasurement, create_wheelmeasurement, do_it, func_arg, testimage, register_comclasscb, do_it2
import cv2

# assert m.__version__ == '0.0.1'
# assert m.add(10, 20) == 30
# # assert m.subtract(1, 2) == -1
# 
# pet = m.Pet("initial name")
# pet.setName("my pet's name")
# name = pet.getName()
# print(name)
 
# def square(i):
#     print('square received {} '.format(i))
#     return
# def rect(i):
#     print('rect received {} '.format(i))
#     return
#   
# func_arg(square)
# func_arg(rect)
# do_it();

def cb(val):
    print(val)
    return

register_comclasscb(cb)
do_it2()
#  
# obj_meas = VOMeasurement(1.3, [4.5,6.7,88], 100)

# test = testimage()
# img = cv2.imread('/home/levin/raw_data/loop_image/52-1-1descriptor_match.jpg')
# test.show_image(img)
# 
# obj_meas = create_vomeasurement(1.3, [4.5,6.7,88], 100)
# obj_meas_2 = create_wheelmeasurement(1.3, [4.5,6.7,88], 2)
# 
# def update_state(meas, X, P):
#     print("update_state called")
#     meas.info();
# #     print("update_state for {}".format(meas.info()))
#     return
#     
# obj_ekf = ekf()
# obj_ekf.regiger_state_sub(update_state)
# obj_ekf.process_measurement(obj_meas)
# obj_ekf.process_measurement(obj_meas_2)


