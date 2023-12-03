import serial  # pip install pyserial
import time
import pandas as pd
import plotly.express as px

## OPEN SERIAL PORT 
while True:
    com_port = input("Enter Port or 'exit' to Exit: ")
    if com_port == "exit":
        exit(0)
    try:
        print(f"Attempting connection on port {com_port}...")
        ser = serial.Serial(port= com_port, baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
        print(f"Connection to port {com_port} successful!\n")
        break
    except Exception as e:
        print("Invalid Port... Please ensure the port name was entered correctly.\n")

## INITIALIZATIONS
NumStrings = ''             # String to store received uint16_t numbers 
NumList = []                # List to store received uint16_t numbers in int form
TimeList = []               # list to store time stamps of received uint16_t numbers
VoltageList = []            # List to store voltage calculated later

resolution = 3 / (2 ** 10)  # Resolution of MCU

## CAPTURE UART DATA
print("Starting data collection...\n")
startTime = time.time()
while(time.time() - startTime < 60):                   # record data for 60 sec
    line = ser.readline()                               # reads uint16_t nums as single bytes till \n n stores in string
    if ((line != b' \n') and (line != b'\n')) :         # ignore any '\n' without num captures
        try:
            NumStrings = NumStrings + line.decode('Ascii')  # Converts string of received uint16_t num to ASCII and combines Rx nums into 1 string
            timestamp = time.time() - startTime             # Time stamp received number
            TimeList.append(timestamp)                      # Append Timestamp to List
        except UnicodeDecodeError as e:
            continue

print("Data collection completed!")
## CLOSE SERIAL PORT
print(f"Closing {com_port} connection...\n")
ser.close()  # Close open serial ports

### DATA CLEANUP
NumStrings = NumStrings.replace('\x00','')  # \x00 seems to be sent with Disp2String()
NumStrings = NumStrings.strip()             # remove unwanted chars and spaces 
NumList = NumStrings.split('\n')            # split string by \n n store in list

### STORE VALUES IN LIST
NumList = [float(elem) for elem in NumList]             # Convert char in List into Float
# print(NumList)

VoltageList = [elem * resolution for elem in NumList]   # Calculate Voltage and store in list
# print(VoltageList)

# print(len(TimeList))
# print(len(NumList))
# print(len(VoltageList))

### CONVERT DATA INTO DATA FRAME
print("Converting to DataFrame...")
ADCdF = pd.DataFrame()
ADCdF['Time (sec)'] = TimeList
ADCdF['Data (ADCBUFF Value)'] = NumList

VdF = pd.DataFrame()
VdF['Time (sec)'] = TimeList
VdF['Data (Voltage)'] = VoltageList
print("Done Converting! \n")

### DATA STATISTICS
print("ADC DataFrame Statisitcs:")
print(ADCdF.describe() + '\n')

print("Voltage DataFrame Statistics:")
print(VdF.describe() + '\n')

### COPY RX DATA AND RX TIME IN CSV AND XLS FILES
print("Saving to .csv and .xlsx...")
ADCdF.to_csv('ADCBuffer.csv', index= True)
ADCdF.to_excel('ADCBuffer.xlsx', sheet_name='New Sheet')

VdF.to_csv('Voltages.csv', index= True)
VdF.to_excel('Voltages.xlsx', sheet_name='New Sheet')
print("Done saving to .csv and .xlsx!\n")

### PLOT Rx DATA VS Rx TIME
print("Plotting Data...")
fig = px.line(ADCdF, x='Time (sec)', y='Data (ADCBUFF Value)', title = 'ADCBUFF Value vs. Time')
fig2 = px.line(VdF, x='Time (sec)', y='Data (Voltage)', title='Voltage vs. Time')

fig.show()
fig2.show()
print("Done Plotting!")
