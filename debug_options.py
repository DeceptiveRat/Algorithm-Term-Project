import gdb

class printItemlist(gdb.Command):
	def __init__(self):
		super(printItemlist, self).__init__("printItemlist", gdb.COMMAND_USER)

	def invoke(self, args, from_tty):
		for i in range(int(args[0])):
			val = gdb.parse_and_eval(f"items[{i}].x")
			print(f"x: {val}")
			val = gdb.parse_and_eval(f"items[{i}].y")
			print(f"y: {val}")
			val = gdb.parse_and_eval(f"items[{i}].z")
			print(f"z: {val}")
			val = gdb.parse_and_eval(f"items[{i}].weight")
			print(f"weight: {val}")
			val = gdb.parse_and_eval(f"items[{i}].xLocation")
			print(f"xLocation: {val}")
			val = gdb.parse_and_eval(f"items[{i}].yLocation")
			print(f"yLocation: {val}")
			val = gdb.parse_and_eval(f"items[{i}].zLocation")
			print(f"zLocation: {val}")
			val = gdb.parse_and_eval(f"items[{i}].bagNumber")
			print(f"bagNumber: {val}")
			print("")

class printBaglist(gdb.Command):
	def __init__(self):
		super(printBaglist, self).__init__("printBaglist", gdb.COMMAND_USER)

	def invoke(self, args, from_tty):
		for i in range(int(args[0])):
			val = gdb.parse_and_eval(f"bags[{i}].x")
			print(f"x: {val}")
			val = gdb.parse_and_eval(f"bags[{i}].y")
			print(f"y: {val}")
			val = gdb.parse_and_eval(f"bags[{i}].z")
			print(f"z: {val}")
			val = gdb.parse_and_eval(f"bags[{i}].maxCapacity")
			print(f"maxCapacity: {val}")
			print("")

printItemlist()
printBaglist()
