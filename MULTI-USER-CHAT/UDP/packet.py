class Packet:
    '''
    H - Hello Packet
    M - Message Packet
    C - Close Packet
    '''
    packet_types = ['H', 'M', 'C']
    def __init__(self, ptype, data=None):
        assert ptype in Packet.packet_types
        self.ptype = ptype
        self.data = data
