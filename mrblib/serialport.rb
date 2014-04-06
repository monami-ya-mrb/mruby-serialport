
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

# modem_params (set)
class SerialPort

  alias_method :modem_params=, :set_modem_params

  def self.baud=(baud)
    raise ArgumentError.new "baud must be from 50 to 256000." if data_bits < 50 or data_bits > 256000
    set_modem_params baud, nil, nil, nil
  end

  def self.data_bits=(data_bits)
    raise ArgumentError.new "data_bits must be from 5 to 8." if data_bits < 5 or data_bits > 8
    set_modem_params nil, data_bits, nil, nil
  end

  def self.stop_bits=(stop_bits)
    raise ArgumentError.new "stop_bits must be from 1 or 2." if stop_bits != 1 and stop_bits != 2
    set_modem_params nil, stop_bits, nil, nil
  end

  def self.parity=(parity)
    if parity != NONE and parity != EVEN and parity != ODD and parity != MARK and parity != SPACE
      raise ArgumentError.new "Invalid value for parity."
    end
    set_modem_params nil, nil, nil, parity
  end

end

