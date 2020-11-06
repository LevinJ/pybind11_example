import sys 
import os
sys.path.append(os.path.join(os.path.dirname(__file__), "../bin"))
import example as m

# assert m.__version__ == '0.0.1'
assert m.add(10, 20) == 30
assert m.subtract(1, 2) == -1
