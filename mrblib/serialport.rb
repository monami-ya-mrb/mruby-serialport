
def SerialPort::new(port, *params)
  serial_port = super(port, "w+")

  begin
    serial_port.set_modem_params(*params)
  rescue
    serial_port.close
    raise
  end
  serial_port
end

class SerialPort

  def self.open(port, *params, &block)
    serial_port = self.new(port, params)

    begin
      yield serial_port

      serial_port.close
      serial_port = nil
    rescue
      serial_port.close
      raise
    end
    serial_port
  end

end
