#include <linux/module.h> /* thu vien nay dinh nghia cac macro nhu module_init va module_exit */
#include <linux/fs.h> /* thư viện này định nghĩa các hàm cấp phát/giải phóng device number */
#include <linux/device.h> /* thư viện này chứa các hàm phục vụ cho việc tạo device file */

#define DRIVER_AUTHOR "Huynh Tan Cuong"
#define DRIVER_DESC   "A sample character device driver"
#define DRIVER_VERSION "0.4"

/// @brief struct của character driver
/**
 * dev_class và dev là để phục vụ cho việc lưu kết quả trả về của hàm class_create và device_create
*/
struct _vchar_drv {
	dev_t dev_num;
	struct class *dev_class;
	struct device *dev; 
} vchar_drv;

/****************************** device specific - START *****************************/
/* ham khoi tao thiet bi */

/* ham giai phong thiet bi */

/* ham doc tu cac thanh ghi du lieu cua thiet bi */

/* ham ghi vao cac thanh ghi du lieu cua thiet bi */

/* ham doc tu cac thanh ghi trang thai cua thiet bi */

/* ham ghi vao cac thanh ghi dieu khien cua thiet bi */

/* ham xu ly tin hieu ngat gui tu thiet bi */

/******************************* device specific - END *****************************/

/******************************** OS specific - START *******************************/
/* cac ham entry points */

/* ham khoi tao driver */
static int __init vchar_driver_init(void)
{
	int ret = 0; // giá trị kiểm tra việc cấp phát device number

	/* cap phat device number */
	vchar_drv.dev_num = 0;
	ret = alloc_chrdev_region(&vchar_drv.dev_num, 0, 1, "vchar_drv");
	if (ret < 0) {
		printk("Failed to register device number dynamically\n");
		goto failed_register_devnum;
	}
	printk("Allocated device number dynamically. Device number is (%d,%d)\n", MAJOR(vchar_drv.dev_num), MINOR(vchar_drv.dev_num));

	/* tao device file */
		/**
		 * Tạo ra một thiết bị có tên là "class_vchar_dev".
		 * Nếu hàm này không thực hiện thành công, ta cần gọi hàm unregister_chrdev_region 
		 * để giải phóng device number đã được cấp phát trước đó.
		*/
	vchar_drv.dev_class = class_create(THIS_MODULE, "class_vchar_dev");
	if (vchar_drv.dev_class == NULL) {
		printk("Failed to create device class\n");
		goto failed_create_class;
	}
		/**
		 * Nếu tạo class thành công, ta tiếp tục gọi hàm device_create để tạo ra một thiết bị có tên là "vchar_dev".
		 * Thiết bị này nằm trong thư mục /dev.
		 * Trong trường hợp hàm device_create không thực hiện được, ta cần gọi hàm destroy_class để giải phóng 
		 * lớp thiết bị đã được tạo ra trước đó.
		*/
	vchar_drv.dev = device_create(vchar_drv.dev_class, NULL, vchar_drv.dev_num, NULL, "vchar_dev");
	if (vchar_drv.dev == NULL) {
		printk("Failed to create device\n");
		goto failed_create_device;
	}

	/* cap phat bo nho cho cac cau truc du lieu cua driver va khoi tao */

	/* khoi tao thiet bi vat ly */

	/* dang ky cac entry point voi kernel */

	/* dang ky ham xu ly ngat */

	printk("Initialize vchar driver successfully\n");
	return 0;

failed_create_device:
	class_destroy(vchar_drv.dev_class);
failed_create_class:
	unregister_chrdev_region(vchar_drv.dev_num, 1);
failed_register_devnum:
	return ret;
}

/* ham ket thuc driver */
static void __exit vchar_driver_exit(void)
{
	/* huy dang ky xu ly ngat */

	/* huy dang ky entry point voi kernel */

	/* giai phong thiet bi vat ly */

	/* giai phong bo nho da cap phat cau truc du lieu cua driver */

	/* xoa bo device file */
	device_destroy(vchar_drv.dev_class, vchar_drv.dev_num);
	class_destroy(vchar_drv.dev_class);

	/* giai phong device number */
	unregister_chrdev_region(vchar_drv.dev_num, 1);

	printk("Exit vchar driver\n");
}
/********************************* OS specific - END ********************************/

module_init(vchar_driver_init);
module_exit(vchar_driver_exit);

MODULE_LICENSE("GPL"); /* giay phep su dung cua module */
MODULE_AUTHOR(DRIVER_AUTHOR); /* tac gia cua module */
MODULE_DESCRIPTION(DRIVER_DESC); /* mo ta chuc nang cua module */
MODULE_VERSION(DRIVER_VERSION); /* mo ta phien ban cuar module */
// MODULE_SUPPORTED_DEVICE("testdevice"); /* kieu device ma module ho tro */