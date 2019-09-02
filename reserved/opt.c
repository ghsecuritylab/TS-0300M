#ifdef CHECKSUM_BY_HARDWARE
/* CHECKSUM_GEN_IP==0: Generate checksums by hardware for outgoing IP packets.*/
#define CHECKSUM_GEN_IP 		0
/* CHECKSUM_GEN_UDP==0: Generate checksums by hardware for outgoing UDP packets.*/
#define CHECKSUM_GEN_UDP 		0
/* CHECKSUM_GEN_TCP==0: Generate checksums by hardware for outgoing TCP packets.*/
#define CHECKSUM_GEN_TCP 		0
/* CHECKSUM_GEN_ICMP==0: Generate checksums by hardware for outgoing ICMP packets.*/
#define CHECKSUM_GEN_ICMP 		0
/* CHECKSUM_GEN_ICMP6==0: Generate checksums by hardware for outgoing ICMP6 packets.*/
#define CHECKSUM_GEN_ICMP6 		0


/* CHECKSUM_CHECK_IP==0: Check checksums by hardware for incoming IP packets.*/
#define CHECKSUM_CHECK_IP 		0
/* CHECKSUM_CHECK_UDP==0: Check checksums by hardware for incoming UDP packets.*/
#define CHECKSUM_CHECK_UDP 		0
/* CHECKSUM_CHECK_TCP==0: Check checksums by hardware for incoming TCP packets.*/
#define CHECKSUM_CHECK_TCP 		0
/* CHECKSUM_GEN_ICMP==0: Check checksums by hardware for incoming ICMP packets.*/
#define CHECKSUM_CHECK_ICMP 	0
/* CHECKSUM_CHECK_ICMP6==0: Check checksums by hardware for incoming ICMP6 packets.*/
#define CHECKSUM_CHECK_ICMP6 	0
#else
/* CHECKSUM_GEN_IP==1: Generate checksums in software for outgoing IP packets.*/
#define CHECKSUM_GEN_IP 		1
/* CHECKSUM_GEN_UDP==1: Generate checksums in software for outgoing UDP packets.*/
#define CHECKSUM_GEN_UDP 		1
/* CHECKSUM_GEN_TCP==1: Generate checksums in software for outgoing TCP packets.*/
#define CHECKSUM_GEN_TCP 		1
/* CHECKSUM_GEN_ICMP==1: Generate checksums in software for outgoing ICMP packets.*/
#define CHECKSUM_GEN_ICMP 		1
/* CHECKSUM_GEN_ICMP6==1: Generate checksums in software for outgoing ICMP6 packets.*/
#define CHECKSUM_GEN_ICMP6 		1

/* CHECKSUM_CHECK_IP==1: Check checksums in software for incoming IP packets.*/
#define CHECKSUM_CHECK_IP 		1
/* CHECKSUM_CHECK_UDP==1: Check checksums in software for incoming UDP packets.*/
#define CHECKSUM_CHECK_UDP 		1
/* CHECKSUM_CHECK_TCP==1: Check checksums in software for incoming TCP packets.*/
#define CHECKSUM_CHECK_TCP 		1
/* CHECKSUM_CHECK_ICMP==1: Check checksums in software for incoming ICMP packets.*/
#define CHECKSUM_CHECK_ICMP 	1
/* CHECKSUM_CHECK_ICMP6==1: Check checksums in software for incoming ICMP6 packets.*/
#define CHECKSUM_CHECK_ICMP6 	1

#endif