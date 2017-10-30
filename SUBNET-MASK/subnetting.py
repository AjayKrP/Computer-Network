class IPv4:
    @staticmethod
    def dec_to_binary(address):
        return list(map(lambda x: bin(x)[2:].zfill(8), address))

    @staticmethod
    def negation_mask(net_mask):
        wild = list()
        for i in net_mask:
            wild.append(255 - int(i))
        return IPv4.dec_to_binary(wild)

    def __init__(self, ip_addr):
        self.address_val, self.cidr = ip_addr.split('/')
        self.address = list(map(int, self.address_val.split('.')))
        self.binary_ip = IPv4.dec_to_binary(self.address)
        self.subnet_mask = self.net_mask()
        self.binary_mask = IPv4.dec_to_binary(self.subnet_mask)
        self.negation_mask = IPv4.negation_mask(self.subnet_mask)

    def net_mask(self):
        mask = [0, 0, 0, 0]
        for i in range(int(self.cidr)):
            mask[i // 8] += 1 << (7 - i % 8)
        return mask

    def broadcast_ip(self):
        broadcast = list()
        for x, y in zip(self.binary_ip, self.negation_mask):
            broadcast.append(int(x, 2) | int(y, 2))
        return broadcast

    def network_ip(self):
        network = list()
        for x, y in zip(self.binary_ip, self.binary_mask):
            network.append(int(x, 2) & int(y, 2))
        return network

    def num_host(self):
        return (2 ** sum(map(lambda x: sum(c == '1' for c in x), self.negation_mask))) - 2

    def ip_range(self):
        min_range = self.network_ip()
        min_range[-1] += 1
        max_range = self.broadcast_ip()
        max_range[-1] -= 1
        return '{} - {}'.format('.'.join(map(str, min_range)), '.'.join(map(str, max_range)))


if __name__ == '__main__':
    ipv4 = IPv4('192.168.56.1/8')
    print('IPv4 Subnet Mask ->', '.'.join(map(str, ipv4.subnet_mask)))
    print('IPV4 Broadcast ->', '.'.join(map(str, ipv4.broadcast_ip())))
    print('IPv4 Network Address ->', '.'.join(map(str, ipv4.network_ip())))
    print('Number of Hosts ->', ipv4.num_host())
    print('IP Range ->', ipv4.ip_range())
