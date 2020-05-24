import time
import turtle
myPen = turtle.Turtle()
myPen.hideturtle()
window = turtle.Screen()
window.bgcolor("#FFFFFF")

def displaytext(text):

    myPen.clear()
    myPen.write(text,False, 'center',font=("Arial" , 24, "normal"))
    time.sleep(1)


while 1:
    while 1:
        displaytext("Welcome!")
        displaytext("Scan QR code to borrow/return")
        qr = False #get from qr scanner
        if qr:
            break
    displaytext("processing... please wait")
    TALK TO SERVER
    displaytext("Please take a umbrella. Enjoy!")
