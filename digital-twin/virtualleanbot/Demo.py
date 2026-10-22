# Demo: motion and gripper on SynapseCity.01.
from pyLeanbot import *

MISSION = 'SynapseCity.01'
SPEED_UP = 1

Leanbot.begin()
print('Starting mission:', MISSION)
LbMission.beginDigitalTwin(MISSION, speedUp=SPEED_UP)

LbGripper.open()
LbMotion.runLR(2000, 2000)
LbDelay(1200)
LbMotion.stopAndWait()
LbGripper.close()

LbMission.end()
print('Mission complete')
