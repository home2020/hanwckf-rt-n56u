#define RTCONFIG_USB

//#define DEBUG_USB

#ifdef DEBUG_USB
#define usb_dbg(fmt, args...) do{ \
		FILE *fp = fopen("/tmp/usb.log", "a+"); \
		if(fp){ \
			fprintf(fp, "[usb_dbg: %s] ", __FUNCTION__); \
			fprintf(fp, fmt, ## args); \
			fclose(fp); \
		} \
	}while(0)
#else
#define usb_dbg(fmt, args...) do{}while(0)
#endif

#define MAX_WAIT_FILE 5
#define SCAN_PRINTER_NODE 2

#define SYS_MODULE "/sys/module"
#define SYS_BLOCK "/sys/block"
#define SYS_TTY "/sys/class/tty"
#define SYS_NET "/sys/class/net"
#define SYS_PRINTER "/sys/class/usb"
#define SYS_SG "/sys/class/scsi_generic"
#define USB_DEVICE_PATH "/sys/bus/usb/devices"
#define USB_BUS_PATH "/proc/bus/usb/devices"

#define USB_EHCI_PORT_1 get_usb_ehci_port(0)
#define USB_EHCI_PORT_2 get_usb_ehci_port(1)
#define USB_OHCI_PORT_1 get_usb_ohci_port(0)
#define USB_OHCI_PORT_2 get_usb_ohci_port(1)

#define USB_PORT_HAS_MODEM_TTY  0x02
#define USB_PORT_HAS_MODEM_ETH  0x04
#define USB_PORT_HAS_PRINTER    0x08

enum {
	DEVICE_TYPE_UNKNOWN=0,
	DEVICE_TYPE_HUB,
	DEVICE_TYPE_DISK,
	DEVICE_TYPE_SG,
	DEVICE_TYPE_CD,
	DEVICE_TYPE_PRINTER,
	DEVICE_TYPE_MODEM_TTY,
	DEVICE_TYPE_MODEM_ETH
};

typedef struct usb_info_t usb_info_t;
struct usb_info_t {
	char *manuf;
	char *product;
	int port_root;
	int id_devnum;
	int id_parent;
	int id_port;
	int dev_type;
	int dev_cls;
	int dev_sub;
	int dev_prt;
	int dev_vid;
	int dev_pid;
	usb_info_t *prev;
	usb_info_t *next;
};


extern int  file_lock(char *tag);
extern void file_unlock(int lockfd);
extern char *get_usb_ehci_port(int port);
extern char *get_usb_ohci_port(int port);
extern int  get_usb_root_port_number(const char *usb_root_port_id);

extern int  get_device_type_by_device(const char *device_name);
extern char *get_usb_path_by_device(const char *device_name, char *buf, const int buf_size);
extern char *get_usb_root_port_by_string(const char *target_string, char *buf, const int buf_size);
extern char *get_usb_root_port_by_device(const char *device_name, char *buf, const int buf_size);
extern char *get_usb_port_by_interface_string(const char *target_string, char *buf, const int buf_size);
extern char *get_usb_port_by_string(const char *target_string, char *buf, const int buf_size);
extern char *get_usb_port_by_device(const char *device_name, char *buf, const int buf_size);
extern char *get_interface_by_string(const char *target_string, char *buf, const int buf_size);
extern char *get_interface_by_device(const char *device_name, char *buf, const int buf_size);

extern char *get_usb_param(const char *usb_string, const char *param, char *buf, const int buf_size);
extern char *get_usb_vid(const char *usb_port_id, char *buf, const int buf_size);
extern char *get_usb_pid(const char *usb_port_id, char *buf, const int buf_size);
extern char *get_usb_manufact(const char *usb_port_id, char *buf, const int buf_size);
extern char *get_usb_product(const char *usb_port_id, char *buf, const int buf_size);
extern char *get_usb_serial(const char *usb_port_id, char *buf, const int buf_size);
extern char *get_usb_interface_class(const char *usb_interface_id, char *buf, const int buf_size);
extern char *get_usb_interface_subclass(const char *usb_interface_id, char *buf, const int buf_size);
extern int  get_interface_numendpoints(const char *usb_interface_id);
extern int  get_interface_Int_endpoint(const char *usb_interface_id);
extern int  get_usb_devnum(const char *usb_port_id);
extern int  get_usb_interface_number(const char *usb_port_id);

extern int  isSerialNode(const char *device_name);
extern int  isACMNode(const char *device_name);
extern int  isWDMNode(const char *device_name);
extern int  isUsbNetIf(const char *device_name);
extern int  isSerialInterface(const char *interface_class);
extern int  isACMInterface(const char *interface_class, const char *interface_subclass);
extern int  isRNDISInterface(const char *interface_class, const char *interface_subclass);
extern int  isCDCEthInterface(const char *interface_class, const char *interface_subclass);
extern int  isCDCNCMInterface(const char *interface_class, const char *interface_subclass);
extern int  isCDCMBIMInterface(const char *interface_class, const char *interface_subclass);
extern int  isStorageInterface(const char *interface_class);

extern int  is_wan_phy_connected(void);
extern int  get_usb_modem_wan(int unit);
extern int  get_usb_modem_dev_wan(int unit, int devnum);
extern void set_usb_modem_dev_wan(int unit, int devnum);

extern int  has_usb_devices(void);
extern usb_info_t *get_usb_info(void);
extern void free_usb_info(usb_info_t *usb_info_list);
