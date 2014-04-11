#assert("serial") do
#  sp = SerialPort.new("/dev/tty.usbserial-A30015j6", 115200, 8, 1, 0)
#  sp.read_timeout=1000
#
#  sp.puts "foobarbaz"
#  sp.gets == "foobarbaz\n"
#end
