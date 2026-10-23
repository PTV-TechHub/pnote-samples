# Leanbot test testCollision() against the Green pollution block
# Start
# - Leanbot at the field centre, facing +X
# - Pollution: Green far in front of the Leanbot
# Leanbot steps
# - Slide the block into the front of the Leanbot, 5 mm at a time
# - Slide the block into the side of the Leanbot, 5 mm at a time
# - Then drive the Leanbot into the block instead, turned 90 degrees
# - Print testCollision() at every step, and compare it with Top View
# - Mission end (Leanbot stops where it is)


# #include <Leanbot.h>
from pyLeanbot2 import *
import SynapseCity as sim              # Synapse City field simulation

holdMs = 600                             # time to hold each pose, so Top View can redraw

ORIGIN = sim.pose(x=0, y=0, rz=0)

def simSetup():                          # place Leanbot and the block on the field
    sim.Leanbot.moveTo(ORIGIN)
    sim.POLUTION.GREEN.moveTo(sim.pose(x=120, y=0, rz=0))

def setup():
    simSetup()
    Leanbot.begin()                      # initialize Leanbot

def loop():
    LbMission.beginDigitalTwin('SynapseCity.01')
    BlockIntoTheFront()
    BlockIntoTheSide()
    LeanbotIntoTheBlock()
    LbMission.end()

def BlockIntoTheFront():                 # expect: frame, from x = 60 inwards
    for x in range(120, 40, -5):
        BlockTo(x, 0)

def BlockIntoTheSide():                  # expect: wheels, from y = 65 inwards
    for y in range(100, 40, -5):
        BlockTo(0, y)

def LeanbotIntoTheBlock():               # same approach turned 90 degrees, same answer
    sim.POLUTION.GREEN.moveTo(sim.pose(x=0, y=0, rz=90))
    for y in range(-150, -20, 10):
        LeanbotTo(0, y, 90)

def BlockTo(x, y):
    sim.POLUTION.GREEN.moveTo(sim.pose(x=x, y=y, rz=0))
    LbDelay(holdMs)                      # hold still, then read
    Report('block  (' + str(x) + ', ' + str(y) + ')')

def LeanbotTo(x, y, rz):
    sim.Leanbot.moveTo(sim.pose(x=x, y=y, rz=rz))
    LbDelay(holdMs)                      # hold still, then read
    Report('leanbot(' + str(x) + ', ' + str(y) + ', ' + str(rz) + ')')

def Report(label):
    hits = sim.testCollision()           # [] means nothing is touching
    if not hits:
        print(label + '   không chạm')
        return
    for hit in hits:                     # one line per part being touched
        print(label + '   ' + hit.part + '  ' + str(round(hit.overlapMm, 2)) + 'mm')

# Main Python code
setup()
loop()
