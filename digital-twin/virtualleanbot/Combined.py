# Leanbot neutralize E2, contain B1 and collect Red pollution at F4
# Start
# - Leanbot at CRL
# - Pollution: Blue at E2, Green at B1, Red at F4
# - Neutralize at S3
# Leanbot steps
# - Follow line to S3
# - Pick up Neutralize at S3
# - Follow line to E2
# - Push Pollution into Containment E
# - Drop Neutralize into Containment E
# - Follow line to B1
# - Push Pollution into Containment B
# - Follow line to F4
# - Pick up Pollution at F4
# - Follow line to CRL
# - Drop Pollution into CRL
# - Mission end (Leanbot stops at CRL)


# #include <Leanbot.h>
from pyLeanbot2 import *
import SynapseCity                     # Synapse City field simulation

speed = 2000

def setupSynapseCity():
    # setup Neutralizer Blocks
    SynapseCity.setBlocks("""
        S3  Blue
    """)
    # setup Pollution Blocks
    SynapseCity.setBlocks("""
        E2  Blue
        B1  Green
        F4  Red
    """)

def setup():
    setupSynapseCity()
    Leanbot.begin()

def loop():
    LbMission.beginDigitalTwin('SynapseCity.01')
    FromCRLtoS3()
    PickupNeutralizeS3()                     # neutralize rides along to E2
    FromS3toE2()
    PushPollutionE2()
    DropNeutralizeE2()
    FromE2toB1()
    PushPollutionB1()
    FromB1toF4()
    PickupPollutionF4()                      # pollution rides along to CRL
    FromF4toCRL()
    DropPollutionCRL()
    LbMission.end()
    SynapseCity.getFinalScore()

def FromCRLtoS3():
    Forward(speed, 110)                            # Go  to the line.
    Rotate(-speed, 108)                            # Turn Left
    followLineMultipleJunctions(2)                 # Move 2 Junctions
    goToJunction()

def PickupNeutralizeS3():
    LbGripper.close(50)                            # Close

def FromS3toE2():
    Rotate(speed, 53)                              # Turn right
    followLineMultipleJunctions(2)                 # Move 2 Junctions
    goToJunction()
    Rotate(speed, 53)
    followLineMultipleJunctions(2)                 # Move 2 Junctions
    goToJunction()
    Rotate(speed, 25)                              # Turn right

def PushPollutionE2():
    Forward(speed, 150)

def DropNeutralizeE2():
    LbGripper.open()

def FromE2toB1():
    Backward(speed, 150)
    Rotate(-speed, 97)                            # Turn left
    followLineMultipleJunctions(2)                 # Move 2 Junctions
    goToJunction()
    Rotate(speed, 53)                              # Turn right
    followLineMultipleJunctions(2)                 # Move 2 Junctions
    goToJunction()
    Rotate(speed, 106)                             # Turn right

def PushPollutionB1():
    Forward(speed, 150)

def FromB1toF4():
    Backward(speed, 150)
    Rotate(-speed, 30)                             # Turn left
    followLineMultipleJunctions(5)                 # Move 5 Junctions
    goToJunction()
    Rotate(-speed, 40)                             # Turn left
    Forward(speed, 30)

def PickupPollutionF4():
    LbGripper.close(50)                            # Close

def FromF4toCRL():
    Backward(speed, 30)
    Rotate(speed, 40)                              # Turn right
    followLineMultipleJunctions(1)                 # Move 1 Junctions
    goToJunction()
    Rotate(speed, 53)                              # Turn right
    followLineMultipleJunctions(2)                 # Move 2 Junctions
    goToJunction()
    Rotate(speed, 30)                              # Turn right

def DropPollutionCRL():
    LbGripper.open()                               # open

def Forward(speed, distanceMm):
    LbMotion.runLR(speed, speed)                  # Move forward with given speed
    LbMotion.waitDistanceMm(distanceMm)           # Wait until distance is reached
    LbMotion.stopAndWait()                        # Stop and wait

def Backward(speed, distanceMm):
    LbMotion.runLR(-speed, -speed)                # Move backward with given speed
    LbMotion.waitDistanceMm(distanceMm)           # Wait until distance is reached
    LbMotion.stopAndWait()                        # Stop and wait

def Rotate(speed, deg):
    LbMotion.runLR(speed, -speed)                 # Rotate robot in place
    LbMotion.waitRotationDeg(deg)                 # Wait until rotation angle is reached
    LbMotion.stopAndWait()                        # Stop and wait

def followLineDistance(distanceMm):
    targetMm = distanceMm + LbMotion.getDistanceMm() # Calculate targ et distance

    while LbMotion.getDistanceMm() < targetMm: 				# Continue until target distance is reached
        runFollowLine()                             				# Run line following logic

def runFollowLine():
    #LbRGB.fillColor(CRGB.Black) # Off RGB
    lineValue = LbIRLine.read()                # Read IR line sensor value
    LbIRLine.displayOnRGB(CRGB.DarkCyan)          # Display sensor status on RGB LED

    match lineValue:

        case 0b0100:                                 # .o..
            LbMotion.runLR(+speed/2, +speed)          # Adjust slightly to the left

        case 0b0010:                                 # ..o.
            LbMotion.runLR(+speed, +speed/2)          # Adjust slightly to the right

        case 0b1100:                                 # oo..
            LbMotion.runLR(     0, +speed)            # Strong left correction

        case 0b0011:                                 # ..oo
            LbMotion.runLR(+speed, 0)                 # Strong right correction

        case 0b1000:                                 # o...
            LbMotion.runLR(-speed/2, +speed/2)        # Sharp left turn

        case 0b0001:                                 # ...o
            LbMotion.runLR(+speed/2, -speed/2)        # Sharp right turn

        case _:
            LbMotion.runLR(+speed, +speed)            # Go straight

def followLineUntilJunction():
    while LbIRLine.read() != 0b1111:            # Continue until full junction is detected
        runFollowLine()                             # Run line following logic

def goToJunction():
    followLineUntilJunction()                     # Continue until junction is detected
    followLineDistance(5)                        # Move forward to the purple block
    LbMotion.stopAndWait()                        # Stop and wait

def followLineMultipleJunctions(junctionCount):
    for i in range(junctionCount):
        followLineDistance(30)
        followLineUntilJunction()

# Main Python code
setup()
loop()
