
class SerialPort

  def self.open(port, *params, &block)
    serial_port = create(port)

    begin
      serial_port.set_modem_params(*params)
      return serial_port unless block

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
