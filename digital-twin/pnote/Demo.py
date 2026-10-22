# Demo: motion and gripper on SynapseCity.01.
# PNote version (Pythaverse2026#652): same as ../virtualleanbot/Demo.py without speedUp, which PNote's pyLeanbot does not accept.
from pyLeanbot import *

MISSION = 'SynapseCity.01'

Leanbot.begin()
print('Starting mission:', MISSION)
LbMission.beginDigitalTwin(MISSION)   # PNote's pyLeanbot takes only the mission id (no speedUp)

LbGripper.open()
LbMotion.runLR(2000, 2000)
LbDelay(1200)
LbMotion.stopAndWait()
LbGripper.close()

LbMission.end()
print('Mission complete')
