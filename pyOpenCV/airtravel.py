class Flight:
	
	# 순서 : new => init 
	# new 이후에
	def __init__(self):
		print("init")
		super().__init__()
	
	# 메모리 할당 될 때
	def __new__(cls):
		print('new')
		return super().__new__(cls)

	def number(self):
		return 'SN060'
