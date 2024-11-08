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

class poppedToPush(gdb.Command):
	def __init__(self):
		super(poppedToPush, self).__init__("poppedToPush", gdb.COMMAND_USER)

	def invoke(self, args, from_tty):
		gdb.execute("display popped")
		gdb.execute("display popped.bagState[0]")
		gdb.execute("display popped.bagState[1]")
		gdb.execute("display toPush")
		gdb.execute("display toPush.bagState[0]")
		gdb.execute("display toPush.bagState[1]")

class displayQueue(gdb.Command):
	def __init__(self):
		super(displayQueue, self).__init__("displayQueue", gdb.COMMAND_USER)

	def invoke(self, args, from_tty):
		if not args:
			print("usage: displayQueue <queue size> <bag count>")
			return

		arguments = args.split()
		front = gdb.parse_and_eval(f"queue.front")
		size = gdb.parse_and_eval(f"queue.size")
		for i in range(int(size)):
			if (i + int(front) >= int(arguments[0])):
				index = i+int(front)-int(arguments[0])
			else:
				index = i + int(front)
				
			print(f"printing queue buffer {index}")
			gdb.execute(f"print queue.buffer[{index}]")
			for j in range(int(arguments[1])):
				print("\t", end="");
				print(f"Printing bag state of buffer {index}")
				print("\t", end="");
				gdb.execute(f"print queue.buffer[{index}].bagState[{j}]")
				gdb.execute(f"set $current = queue.buffer[{index}].bagState[{j}].firstItemPtr")
				while True:
					current = gdb.parse_and_eval("$current")
					if current == 0:
						break
					print("\t\t", end="");
					print(f"printing current item")
					print("\t\t", end="");
					gdb.execute(f"print $current->item")
					gdb.execute(f"set $current = $current->nextItemOnList")

printItemlist()
printBaglist()
poppedToPush()
displayQueue()
