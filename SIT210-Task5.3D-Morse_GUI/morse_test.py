# Test more code library
import datetime
import morse_code as MC

## Arrange
last_timestamp = datetime.datetime.now()
timing_list = []

def fnOn2():
    global last_timestamp
    #global timing_str
    current_timestamp = datetime.datetime.now()
    dif = (current_timestamp - last_timestamp).total_seconds()
    timing_list.append(round(dif,1))
    last_timestamp = current_timestamp
    

def fnOff2():
    global last_timestamp
    current_timestamp = datetime.datetime.now()
    dif = (current_timestamp - last_timestamp).total_seconds()
    timing_list.append(round(dif,1))
    last_timestamp = current_timestamp
    
## Act
MC.reader("testing the library", fnOn2, fnOff2)

## Assert
result = [0.0, 1.5, 1.5, 0.5, 1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.5, 1.5, 1.5, 0.5, 0.5, 0.5, 1.5, 1.5, 0.5, 0.5, 1.5, 1.5, 0.5, 1.5, 0.5, 0.5, 3.5, 1.5, 1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.5, 0.5, 3.5, 0.5, 0.5, 1.5, 0.5, 0.5, 0.5, 0.5, 1.5, 0.5, 0.5, 0.5, 1.5, 1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.5, 0.5, 0.5, 1.5, 0.5, 0.5, 1.5, 0.5, 0.5, 1.5, 1.5, 0.5, 0.5, 1.5, 0.5, 0.5, 1.5, 1.5, 0.5, 0.5, 0.5, 1.5, 0.5, 1.5]
assert_equal = True
for i, v in enumerate(result):
    if(timing_list[i] != v):
        assert_equal = False
        
if assert_equal == True:
    print('Morse code reader working as expected.')
else:
    print('Morse code library not working as expected.')
