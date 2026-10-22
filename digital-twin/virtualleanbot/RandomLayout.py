# Works in VirtualLeanbot's Python runner; it does not require RC_Control.py.
from pyLeanbot2 import *
import SynapseCity as sim

# EXPLORER: 4 pollution blocks; CREATOR: 5; INNOVATOR: 6;
# MASTER: 7, including Mystery. Omit the argument for MASTER.
# Mystery is an unknown/non-standard color; white is only its visual placeholder.
LEVEL = 'MASTER'


def setup():
    Leanbot.begin()
    layout = sim.setBlocksRandom(LEVEL)
    print(layout)  # Save this text and pass it to sim.setBlocks() to reuse it.


def loop():
    LbMission.beginDigitalTwin('SynapseCity.01')
    LbMission.end()
    sim.getFinalScore()
