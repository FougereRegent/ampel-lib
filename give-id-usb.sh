#!/bin/sh

vendor='0d50'

displayInformation () {
  usb_string=$1

  product_name=$(echo $usb_string | cut -d" " -f7-)
  id=$(echo $usb_string | cut -d" " -f6 | cut -d: -f2)
  echo "Product Name : ${product_name}"
  echo "Vendor : ${vendor}"
  echo "Id : ${id}"
}

usb_device=()

while IFS= read -r line; do 
  usb_device+=("$line")
done < <(lsusb -d "$vendor":)

if [ ${#usb_device[@]} -lt 1 ]; then
  echo "Cannot find any vendor of ampel product"
  exit -1
fi

for device in "${usb_device[*]}"; do 
  displayInformation "$device"
done


