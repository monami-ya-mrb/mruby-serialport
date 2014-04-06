
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

# modem_params (get)
class SerialPort

  alias_method :modem_params, :get_modem_params

  def self.baud
    params = get_modem_params
    raise new NotImplementedError unless params.key? :baud
    params[:baud]
  end

  def self.data_bits
    params = get_modem_params
    raise new NotImplementedError unless params.key? :data_bits
    params[:data_bits]
  end

  def self.stop_bits
    params = get_modem_params
    raise new NotImplementedError unless params.key? :stop_bits
    params[:stop_bits]
  end

  def self.parity
    params = get_modem_params
    raise new NotImplementedError unless params.key? :parity
    params[:parity]
  end

end
