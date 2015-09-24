#!/usr/bin/python

"""
This example creates a multi-controller network from semi-scratch by
using the net.add*() API and manually starting the switches and controllers.
This is the "mid-level" API, which is an alternative to the "high-level"
Topo() API which supports parametrized topology classes.
Note that one could also create a custom switch class and pass it into
the Mininet() constructor.
"""

from mininet.net import Mininet
from mininet.node import RemoteController, OVSSwitch
from mininet.cli import CLI
from mininet.log import setLogLevel

def multiControllerNet():
    "Create a network from semi-scratch with multiple controllers."

    net = Mininet( controller=RemoteController, switch=OVSSwitch )

    #print "*** Creating (reference) controllers"
    c1 = net.addController( 'c1', controller=RemoteController, ip="127.0.0.1", port=6633 )

    print "*** Creating switches"
    s1 = net.addSwitch( 's1' )
    s2 = net.addSwitch( 's2' )
    s3 = net.addSwitch( 's3' )
    arr = [100, 101, 102]

    print "*** Creating hosts"
    hosts1 = [ net.addHost( 'h%d' % n ) for n in 3, 4 ]
    hosts2 = [ net.addHost( 'h%d' % n ) for n in range(5,10) ]
    hosts3 = [ net.addHost( 'h%d' % n ) for n in arr]

    print "*** Creating links"
    for h in hosts1:
        net.addLink( s1, h )
    for h in hosts2:
        net.addLink( s2, h )
    for h in hosts3:
        net.addLink( s3, h )
    net.addLink(s1,s2)
    net.addLink(s2,s3)

    print "*** Starting network"
    net.build()
    c1.start()
    s1.start( [ c1 ] )
    s2.start( [ c1 ] )
    s3.start( [ c1 ] )

    #print "*** Testing network"
    #net.pingAll()

    print "*** Running CLI"
    CLI( net )

    print "*** Stopping network"
    net.stop()

if __name__ == '__main__':
    setLogLevel( 'info' )  # for CLI output
    multiControllerNet()
