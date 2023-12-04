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
        print(f"Connection to port {com_port} successful!")
        break
    except Exception as e:
        print("Invalid Port... Please ensure the port name was entered correctly.")

## INITIALIZATIONS
NumStrings = ''             # String to store received uint16_t numbers 
DutyCycleList = []          # List to store received uint16_t numbers in int form
TimeList = []               # list to store time stamps of received uint16_t numbers
VpwmList = []               # List to store average PWM voltage calculated later

voltage_resolution = 3 / 100  # Average Voltage

## CAPTURE UART DATA
print("Starting data collection...")
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
print(f"Closing {com_port} connection...")
ser.close()  # Close open serial ports

### DATA CLEANUP
NumStrings = NumStrings.replace('\x00','')  # \x00 seems to be sent with Disp2String()
NumStrings = NumStrings.strip()             # remove unwanted chars and spaces 
DutyCycleList = NumStrings.split('\n')            # split string by \n n store in list

### STORE VALUES IN LIST
DutyCycleList = [float(elem) for elem in DutyCycleList]             # Convert char in list into Float
VpwmList = [elem * voltage_resolution for elem in DutyCycleList]    # Calculate Voltage and store in list

### CONVERT DATA INTO DATA FRAME
print("Converting to DataFrame...")
IntensityDF = pd.DataFrame()
IntensityDF['Time (sec)'] = TimeList
IntensityDF['Data (Light Intensity)'] = DutyCycleList

VoltageDF = pd.DataFrame()
VoltageDF['Time (sec)'] = TimeList
VoltageDF['Data (Voltage)'] = VpwmList
print("Done Converting!")

### DATA STATISTICS
print("ADC DataFrame Statisitcs:")
print(IntensityDF.describe())

print("Voltage DataFrame Statistics:")
print(VoltageDF.describe())

### COPY RX DATA AND RX TIME IN CSV AND XLS FILES
print("Saving to .xlsx...")

with pd.ExcelWriter('AppProject2.xlsx') as writer:
    IntensityDF.to_excel(writer, sheet_name='Intensity')
    VoltageDF.to_excel(writer, sheet_name='Average Voltage')

print("Done saving to .csv and .xlsx!")

### PLOT Rx DATA VS Rx TIME
print("Plotting Data...")
fig = px.line(IntensityDF, x='Time (sec)', y='Data (Light Intensity)', title = 'Light Intensity vs. Time')
fig2 = px.line(VoltageDF, x='Time (sec)', y='Data (Voltage)', title='Average PWM Voltage vs. Time')

fig.show()
fig2.show()
print("Done Plotting!")
