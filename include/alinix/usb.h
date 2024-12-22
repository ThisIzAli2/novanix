/**
 * @author Ali Mirmohammad
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @file usb.h
 * @abstraction:
 * 	- Kernel USB header file.
 * 	- Useful tools and macros.
*/
#ifndef __ALINIX_KERNEL_USB_H
#define __ALINIX_KERNEL_USB_H

#include <alinix/kernel.h>



/**
 * @brief Structure for USB device util .
*/
struct usb_device {
	int		devnum;
	char		devpath[16];
	u32		route;
	// enum usb_device_state	state;
	// enum usb_device_speed	speed;
	unsigned int		rx_lanes;
	unsigned int		tx_lanes;
	// enum usb_ssp_rate	ssp_rate;

	// struct usb_tt	*tt;
	int		ttport;

	unsigned int toggle[2];

	struct usb_device *parent;
	// struct usb_bus *bus;
	// struct usb_host_endpoint ep0;

	struct device dev;

	// struct usb_device_descriptor descriptor;
	// struct usb_host_bos *bos;
	// struct usb_host_config *config;

	// struct usb_host_config *actconfig;
	// struct usb_host_endpoint *ep_in[16];
	// struct usb_host_endpoint *ep_out[16];

	char **rawdescriptors;

	unsigned short bus_mA;
	u8 portnum;
	u8 level;
	u8 devaddr;

	unsigned can_submit:1;
	unsigned persist_enabled:1;
	unsigned reset_in_progress:1;
	unsigned have_langid:1;
	unsigned authorized:1;
	unsigned authenticated:1;
	unsigned lpm_capable:1;
	unsigned lpm_devinit_allow:1;
	unsigned usb2_hw_lpm_capable:1;
	unsigned usb2_hw_lpm_besl_capable:1;
	unsigned usb2_hw_lpm_enabled:1;
	unsigned usb2_hw_lpm_allowed:1;
	unsigned usb3_lpm_u1_enabled:1;
	unsigned usb3_lpm_u2_enabled:1;
	int string_langid;

	/* static strings from the device */
	char *product;
	char *manufacturer;
	char *serial;

	struct list_head filelist;

	int maxchild;

	u32 quirks;
	atomic_t urbnum;

	unsigned long active_duration;

	unsigned long connect_time;

	unsigned do_remote_wakeup:1;
	unsigned reset_resume:1;
	unsigned port_is_suspended:1;

	int slot_id;
	// struct usb2_lpm_parameters l1_params;
	// struct usb3_lpm_parameters u1_params;
	// struct usb3_lpm_parameters u2_params;
	unsigned lpm_disable_count;

	u16 hub_delay;
	unsigned use_generic_driver:1;
};


/**	
 * @brief URB device structure.
*/
struct urb {
	/* private: usb core and host controller only fields in the urb */
	struct kref kref;		/* reference count of the URB */
	int unlinked;			/* unlink error code */
	void *hcpriv;			/* private data for host controller */
	atomic_t use_count;		/* concurrent submissions counter */
	atomic_t reject;		/* submissions will fail */

	/* public: documented fields in the urb that can be used by drivers */
	struct list_head urb_list;	/* list head for use by the urb's
					 * current owner */
	struct list_head anchor_list;	/* the URB may be anchored */
	// struct usb_anchor *anchor;
	struct usb_device *dev;		/* (in) pointer to associated device */
	// struct usb_host_endpoint *ep;	/* (internal) pointer to endpoint */
	unsigned int pipe;		/* (in) pipe information */
	unsigned int stream_id;		/* (in) stream ID */
	int status;			/* (return) non-ISO status */
	unsigned int transfer_flags;	/* (in) URB_SHORT_NOT_OK | ...*/
	void *transfer_buffer;		/* (in) associated data buffer */
	u64 transfer_dma;	/* (in) dma addr for transfer_buffer */
	// struct scatterlist *sg;		/* (in) scatter gather buffer list */
	int num_mapped_sgs;		/* (internal) mapped sg entries */
	int num_sgs;			/* (in) number of entries in the sg list */
	u32 transfer_buffer_length;	/* (in) data buffer length */
	u32 actual_length;		/* (return) actual transfer length */
	unsigned char *setup_packet;	/* (in) setup packet (control only) */
	u64 setup_dma;		/* (in) dma addr for setup_packet */
	int start_frame;		/* (modify) start frame (ISO) */
	int number_of_packets;		/* (in) number of ISO packets */
	int interval;			/* (modify) transfer interval
					 * (INT/ISO) */
	int error_count;		/* (return) number of ISO errors */
	void *context;			/* (in) context for completion */
	// usb_complete_t complete;	/* (in) completion routine */
	// struct usb_iso_packet_descriptor iso_frame_desc[];
					/* (in) ISO ONLY */
};

#endif // __ALINIX_KERNEL_USB_H