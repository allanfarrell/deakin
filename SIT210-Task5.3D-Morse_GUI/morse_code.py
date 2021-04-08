## Morse code library
#
# Morse code timing rules from, https://www.codebug.org.uk/learn/step/541/morse-code-timing-rules/
# dot is 500
# dash is 1500
# space between symbols is 500
# space between letters is 1500
# space between words is 3500
import time

# Components
def symbol_space():
    #print('symbol')
    time.sleep(0.5)

def letter_space():
    #print('letter')
    time.sleep(1.5)
    
def word_space():
    #print('word')
    time.sleep(3.5)
    
def dot():
    #print('dot')
    time.sleep(0.5)
    
def dash():
    #print('dash')
    time.sleep(1.5)
    
#
def controller(letter, fn_on, fn_off):
    symbols = len(morse_alpha[letter]) - 1
    for i, k in enumerate(morse_alpha[letter]):
        if k == 'dot':
            try:
                fn_on()
                dot()
            except:
                print("Callback function fn_on is invalid")
        elif k == 'dash':
            try:
                fn_on()
                dash()
            except:
                print("Callback function fn_on is invalid")   
        if i < symbols:
            try:
                fn_off()
                symbol_space()
            except:
                print("Callback function fn_off is invalid")

#
def reader(morse_str, fn_on, fn_off):
    prev_char = '';
    for letter in morse_str:
        # Perform the actions for the current character
        if letter in morse_alpha:
            # Check the previous character to determine the timing space
            if prev_char in morse_alpha.keys():
                fn_off()
                letter_space()
            controller(letter, fn_on, fn_off)
            prev_char = letter
        elif letter == ' ':
            fn_off()
            word_space()
            prev_char = ' '
        else:
            print("An invalid character has been detected. Character will be skipped.")
    fn_off()

# Alphabet dictionary
morse_alpha = {
    "a": ['dot', 'dash'],
    "b": ['dash', 'dot', 'dot', 'dot'],
    "c": ['dash', 'dot', 'dash', 'dot'],
    "d": ['dash', 'dot', 'dot'],
    "e": ['dot'],
    "f": ['dot', 'dot', 'dash', 'dot'],
    "g": ['dash', 'dash', 'dot'],
    "h": ['dot', 'dot', 'dot', 'dot'],
    "i": ['dot', 'dot'],
    "j": ['dot', 'dash', 'dash', 'dash'],
    "k": ['dash', 'dot', 'dash'],
    "l": ['dot', 'dash', 'dot', 'dot'],
    "m": ['dash', 'dash'],
    "n": ['dash', 'dot'],
    "o": ['dash', 'dash', 'dash'],
    "p": ['dot', 'dash', 'dash', 'dot'],
    "q": ['dash', 'dash', 'dot', 'dash'],
    "r": ['dot', 'dash', 'dot'],
    "s": ['dot', 'dot', 'dot'],
    "t": ['dash'],
    "u": ['dot', 'dot', 'dash'],
    "v": ['dot', 'dot', 'dot', 'dash'],
    "w": ['dot', 'dash', 'dash'],
    "x": ['dash', 'dot', 'dot', 'dash'],
    "y": ['dash', 'dot', 'dash', 'dash'],
    "z": ['dash', 'dash', 'dot', 'dot'],
    '0': ['dash', 'dash', 'dash', 'dash', 'dash'],
    '1': ['dot','dash','dash','dash','dash'],
    '2': ['dot', 'dot','dash','dash','dash'],
    '3': ['dot', 'dot', 'dot', 'dash','dash'],
    '4': ['dot', 'dot', 'dot', 'dot', 'dash'],
    '5': ['dot', 'dot', 'dot', 'dot', 'dot'],
    '6': ['dash', 'dot', 'dot', 'dot', 'dot'],
    '7': ['dash', 'dash', 'dot', 'dot', 'dot'],
    '8': ['dash', 'dash', 'dash', 'dot', 'dot'],
    '9': ['dash', 'dash', 'dash', 'dash', 'dot']}