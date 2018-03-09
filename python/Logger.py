import pyLogger

class Logger:
	def __init__(self):
	   """Initialize a logger object"""
		_log=pyLogger.get()

	def createFileBuffer(self,nm,fle,nflush=100):
		"""Create File buffer
		    nm- Name of the buffer
		    fle- Name of the file to write to
		    nflush - How often to flush the buffer"""
		    self._log.createFileBuffer(nm,fle,nflush)

	def createErrBuffer(self,nm,nflush=100):
		"""Create error buffer
		  nm- Name of the buffer
		  nflush - How often to flush"""
		self._log.createErrBuffer(nm,nflush)
	def flush(self):
		"""Flush all the buffers"""
		self._log.flush()
	def addMessage(self,buff,msg):
		"""Add a message to a given buffer"""
		self._log.addMessage(buff,msg)

	def get(self,buff):
		"""Get the contents of the specified buffer"""
		return self._log.get(buff)





log=Logger();

