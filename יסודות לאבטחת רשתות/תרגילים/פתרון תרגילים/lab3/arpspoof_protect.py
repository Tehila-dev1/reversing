from scapy.all import *
from collections import defaultdict
import time

# משתנים גלובליים
diff_mac = {}
packet_count = defaultdict(list)  # מילון לספירת חבילות לפי IP
attack_threshold = 30             # סף חבילות לזיהוי מתקפה
time_window = 10                  # חלון זמן לבדיקה (שניות)
flag_noMatch = False
flag_packet_rate = False

def noMatch(packet):
    """ זיהוי ARP Spoofing על פי MAC משתנה """
    global flag_noMatch
    ip_src = packet[ARP].psrc
    mac_src = packet[ARP].hwsrc

    # אם הכתובת כבר קיימת במילון
    if ip_src in diff_mac:
        # אם כתובת ה-MAC שונה מהקודמת – נתריע על מתקפה
        if diff_mac[ip_src] != mac_src:
            print(f"⚠️ ARP Spoofing Detected! IP {ip_src} has multiple MACs: {diff_mac[ip_src]} and {mac_src}")
            flag_noMatch = True
    else:
        # הוספת IP-MAC חדש למילון
        diff_mac[ip_src] = mac_src

def check_packet_rate(ip_src):
    """ בדיקה אם נשלחו הרבה חבילות בזמן קצר """
    global packet_count, flag_packet_rate

    current_time = time.time()
    packet_count[ip_src].append(current_time)

    # הסרת חבילות ישנות מחלון הזמן
    packet_count[ip_src] = [t for t in packet_count[ip_src] if current_time - t <= time_window]

    # אם יש יותר חבילות מהסף – נתריע
    if len(packet_count[ip_src]) > attack_threshold:
        print(f"⚠️ High packet rate detected from IP {ip_src} - {len(packet_count[ip_src])} packets in {time_window} seconds")
        flag_packet_rate = True

def check_attack_status():
    """ בדיקה אם שני הדגלים פעילים """
    if flag_noMatch and flag_packet_rate:
        print("⚠️🚨 You are under a combined ARP Spoofing and Packet Flood attack!")
    elif flag_noMatch:
        print("⚠️ ARP Spoofing attack detected!")
    elif flag_packet_rate:
        print("⚠️ Packet Flood attack detected!")
    else:
        print("No attack detected.")

def packet_ARP(packet):
    """ טיפול בחבילות ARP """
    if ARP in packet:
        ip_src = packet[ARP].psrc

        # בדיקת ARP Spoofing
        if packet[ARP].op == 2:
            noMatch(packet)

        # בדיקת כמות חבילות
        check_packet_rate(ip_src)

        # בדיקת מצב מתקפה
        check_attack_status()

def main():
    sniff(filter="arp", prn=packet_ARP, store=False)

if __name__ == "__main__":
    main()