


def freq_analysis(cipher_text):
    chars = 0
    result = {}
    for char in cipher_text:
        if char != " ":
            if char in result.keys():
                result[char] += 1
            else:
                result[char] = 1
            chars += 1
    for key in result:
        result[key] = result[key] / chars
    return result

with open("sub_cipher_text", "r") as input_file:
    cipher_text = input_file.read()

print(cipher_text)
result = freq_analysis(cipher_text)
sorted_dict = {k: v for k, v in sorted(result.items(), key=lambda item: item[1], reverse=True)}
print(sorted_dict)

הנה הקוד שמופיע בתמונה:  


done = False
decrypt_dict = {}

while not done:
    decrypt_text = cipher_text
    letter = input("Which letter would you like to add? 0 to quit\n")
    if letter == "0":
        break
    code = input("Enter code for the letter\n")
    decrypt_dict[letter] = code
    for key in decrypt_dict:
        decrypt_text = decrypt_text.replace(decrypt_dict[key], key.lower())
    print(decrypt_text)
