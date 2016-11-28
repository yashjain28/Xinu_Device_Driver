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
	op_write = "#include <xinu.h>\ndevcall temp"+device_function+"(struct dentry *devptr,char* buf,int32 count){\n\tint32 pinno = "+device_pinno+";\n\tread("+ device_type + \
           ",buf,pinno);\n\tint16 data;\n\tint16 temp;\n\tint32 tempx100;\n\tfloat temperatureval = 0;\n\n\tdata = buf[1]; \n\t temp = buf[0];\n"+\
            "\ttemp = (data<<8)|temp;\n\t//if high voltage is 3.3, if its 5 mulitply by 5.0; \n\t temperatureval = "+ device_formula + \
            ";\n\t tempx100 = (int32)(temperatureval*100);\n\treturn tempx100;\n}"


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
	           "\n\tif(!strcmp(buf,\""+device_attribute1+"\"))"+\
	           "\n\t{\n\t\tbuf[0] = "+device_formula+";\n\t}\n\telse if(!strcmp(buf,\""+device_attribute2+"\"))\n\t{\n\t\tbuf[0] = pinno;\n\t}\n\t"+device_function+\
	           "("+device_type+",buf,count);\n\treturn OK;\n}"

	fp.write(op_write)

device_name = data["devices"][2]["name"]
device_id = data["devices"][2]["id"]
device_function = data["devices"][2]["function"]
device_pinno0F = data["devices"][2]["pinno0F"]
device_pinno0B = data["devices"][2]["pinno0B"]
device_pinno1F = data["devices"][2]["pinno1F"]
device_pinno1B = data["devices"][2]["pinno1B"]

if device_name == "motor":
	fp = open('../device/motor/motorwrite.c', 'w')
	op_write = "#include <xinu.h>\ndevcall motorwrite(struct dentry *devptr,char *buf,uint32 count)"+\
	            "\n{\n\tint32 motorF[2],motorB[2];//index 0 for motor 1 and index 1 for motor 2\n\tmotorF[0] = "+device_pinno0F+";\n\tmotorB[0] = "+\
	            device_pinno1F+";\n\tmotorF[1] = "+device_pinno1F+";\n\tmotorB[1] = "+device_pinno1B+";\n\tif(count == 1)\n\t{\n\t\t"+\
	            device_function+"(motor1,forwarddir);\n\t\t"+device_function+"(motor2,forwarddir);\n\t}\n\telse if(count == 2)\n\t{\n\t\t"+\
	            device_function+"(motor1,backwarddir);\n\t\t"+device_function+"(motor2,backwarddir);\n\t}\n\telse if(count == 3)\n\t{\n\t\t"+\
	            device_function+"(motor1,stopdir);\n\t\t"+device_function+"(motor2,forwarddir);\n\t}\n\telse if(count == 4)\n\t{\n\t\t"+\
	            device_function+"(motor1,forwarddir);\n\t\t"+device_function+"(motor2,stopdir);\n\t}\n\telse if(count == 5)\n\t{\n\t\t"+\
	            device_function+"(motor1,stopdir);\n\t\t"+device_function+"(motor2,stopdir);\n\t}\n\treturn OK;\n}"

	fp.write(op_write)


