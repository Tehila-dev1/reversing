FREQ_TABLE = [12.02, 9.1, 8.12, 7.68, 7.31, 6.95, 6.28, 6.02, 5.92, 4.32, 3.98, 2.88, 2.71, 2.61,
              2.3, 2.11, 2.09, 2.03, 1.82, 1.49, 1.11, 0.69, 0.17, 0.11, 0.1, 0.07]

FREQ_TABLE[:] = [x/100 for x in FREQ_TABLE]

def remove_spaces(text):
    return text.replace(" ", "")

def freq_analysis(cipher_text, key_len, to_print=False):
    chars = 0
    result = {}
    
    for char in cipher_text[:key_len]:
        if char != " ":
            if char in result.keys():
                result[char] += 1
            else:
                result[char] = 1
            chars += 1
            
    for key in result:
        result[key] = result[key] / chars
        
    result = {k: v for k, v in sorted(result.items(), key=lambda item: item[1], reverse=True)}
    
    if to_print:
        print(result)
    return result

def calc_square_diff(sorted_freq_values):
    sum_squares = 0
    for index in range(len(sorted_freq_values)):
        sum_squares += (sorted_freq_values[index] - FREQ_TABLE[index])**2
    return sum_squares

def find_key_len(cipher_text):
    for key_len in range(1, 13):
        letter_freq_dict = freq_analysis(cipher_text, key_len)
        diff = calc_square_diff(list(letter_freq_dict.values()))
        print("Key length: {} Distance: {}".format(key_len, diff*10000))




with open (FILENAME, "r") as input_file:
    cipher_text = input_file.read()
cipher_text = remove_spaces(cipher_text)
find_key_len(cipher_text)
key_len = int(input("What is the key length? "))

for i in range(key_len):
    letter_freq_dict = freq_analysis(cipher_text[i:], key_len)
    cipher_of_E = list(letter_freq_dict.items())[0][0]
    print(chr((ord(cipher_of_E) - ord("E")) % 26 + ord("A")), end="")

        