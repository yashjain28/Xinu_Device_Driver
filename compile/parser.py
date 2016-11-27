import json
from pprint import pprint

with open('ddl.json') as data_file:
	data = json.load(data_file)

# pprint(data)
device_name = data["devices"][0]["name"]
device_id = data["devices"][0]["id"]
device_function = data["devices"][0]["function"]
device_pinno = data["devices"][0]["pinno"]
device_type = data["devices"][0]["devicetype"]
device_measurement = data["devices"][0]["measurement"]
device_formula = data["devices"][0]["formula"]

if device_name == "temperaturesensor":
	fp = open('../device/tempsensor/tempread.c','w')
	op_write = "#include <xinu.h>\ndevcall temp"+device_function+"(struct dentry *devptr,char* buf,int32 count){\n\tread("+ device_type + \
           ",buf,2);\n\tint16 data;\n\tint16 temp;\n\tint32 tempx100;\n\tfloat temperatureval = 0;\n\n\tdata = buf[1]; \n\t temp = buf[0];\n"+\
            "\ttemp = (data<<8)|temp;\n\t//if high voltage is 3.3, if its 5 mulitply by 5.0; \n\t temperatureval = "+ device_formula + \
            ";\n\t tempx100 = (int32)temperatureval*100;\n\treturn tempx100;\n}"


	fp.write(op_write)


device_name = data["devices"][1]["name"]
device_id = data["devices"][1]["id"]
device_function = data["devices"][1]["function"]
device_pinno = data["devices"][1]["pinno"]
device_type = data["devices"][1]["devicetype"]
device_formula = data["devices"][1]["formula"]
device_attribute1 = data["devices"][1]["attribute1"]
device_attribute2 = data["devices"][1]["attribute2"]

if device_name == "led":
	fp = open('../device/led/ledwrite.c', 'w')
	op_write = "#include <xinu.h>\ndevcall "+device_name+device_function+"(struct dentry *devptr,char *buf,uint32 count)\n{\n\t"+"int32 pinno = "+device_pinno+";"+\
	           "\n\tif(!strcpy(buf,\""+device_attribute1+"\"))"+\
	           "\n\t{\n\t\tbuf[0] = "+device_formula+";\n\t}\n\telse if(!strcpy(buf,\""+device_attribute2+"\"))\n\t{\n\t\tbuf[0] = pinno;\n\t}\n\t"+device_function+\
	           "("+device_type+",buf,count);\n\treturn OK;\n}"

	fp.write(op_write)

device_name = data["devices"][2]["name"]
device_id = data["devices"][2]["id"]
device_function = data["devices"][2]["function"]
device_pinno = data["devices"][2]["pinno"]
device_type = data["devices"][2]["devicetype"]
device_formula = data["devices"][1]["formula"]
device_attribute1 = data["devices"][2]["attribute1"]
device_attribute2 = data["devices"][2]["attribute2"]

if device_name == "motor":
	fp = open('../device/motor/motorwrite.c', 'w')
	op_write = "#include <xinu.h>\ndevcall "+device_name+device_function+"(struct dentry *devptr,char *buf,uint32 count)\n{\n\t"+"int32 pinno = "+device_pinno+";"+\
	           "\n\tif(!strcpy(buf,\""+device_attribute1+"\"))"+\
	           "\n\t{\n\t\tbuf[0] = "+device_formula+";\n\t}\n\telse if(!strcpy(buf,\""+device_attribute2+"\"))\n\t{\n\t\tbuf[0] = pinno;\n\t}\n\t"+device_function+\
	           "("+device_type+",buf,count);\n\treturn OK;\n}"

	fp.write(op_write)


