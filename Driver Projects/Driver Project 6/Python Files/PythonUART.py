import serial  # pip install pyserial  or conda install pyserial
import time
import pandas as pd

import plotly.express as px

## OPEN SERIAL PORT 
ser = serial.Serial(port= "COM3", baudrate= 9600, bytesize= 8, timeout= 2, stopbits= serial.STOPBITS_ONE)

## INITIALIZATIONS
rxNumsStr = ''      #string to store received uint16_t numbers 
rxNumsList = []      #List to store received uint16_t numbers in int form 
rxTimesList = []   #list to store time stamps of received uint16_t numbers
startTime = time.time()

## CAPTURE UART DATA
while(time.time() - startTime <= 10):                   # record data for 10 sec
    line = ser.readline()                               # reads uint16_t nums as single bytes till \n n stores in string
    if ((line != b' \n') and (line != b'\n')) :         # removes any '\n' without num captures
        rxNumsStr = rxNumsStr + line.decode('Ascii')    # Converts string of received uint16_t num to ASCII and combines Rx nums into 1 string
        timestamp = time.time() - startTime             # Time stamp received number
        rxTimesList.append(timestamp)                   # save time stamps in a list

## CLOSE SERIAL PORT    
ser.close()  # close any open serial ports

### Rx DATA CLEANUP AND STRING TO FLOAT CONVERSION
rxNumsStr = rxNumsStr.replace('\x00','')  #\x00 seems to be sent with Disp2String()
rxNumsStr = rxNumsStr.strip() # remove unwanted chars and spaces 
rxNumsList = rxNumsStr.split(' \n ')  # split string by \n n store in list
print(rxNumsList)
rxNumsList = [float(elem) for elem in rxNumsList]  # convert char in List into int

# print(rxNumsList)       #check
print(len(rxTimesList))
print(len(rxNumsList))

### CONVERT Rx DATA INTO DATA FRAME
dF = pd.DataFrame()
dF['Rx Time (sec)'] = rxTimesList
dF['Rx Data'] = rxNumsList

### DATA STATISTICS
print(dF.describe())

### COPY RX DATA AND RX TIME IN CSV AND XLS FILES
dF.to_csv('RxDataFloat.csv', index= True)
dF.to_excel('RxDataFloat.xlsx', sheet_name='New Sheet')

### PLOT Rx DATA VS Rx TIME
fig = px.line(dF, x='Rx Time (sec)', y='Rx Data', title = 'RS232 Data vs Time')
fig.show()
