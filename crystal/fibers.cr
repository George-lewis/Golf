##################################################
# Simple demonstration of concurrency in Crystal #
#    Note: Because this isn't true paralellism   #
#       There is likely no benefit to this       #
##################################################

module Fibers
  chan = Channel(UInt8).new
  i = 0
  loop do
    spawn do
      loop do
        x = (rand() * 10).to_u8()
        if x % 2 == 0
          chan.send(x)
        end
      end
    end
    break if (i += 1) == 10
  end

  a = chan.receive()
  chan.close()
  puts "Got #{a}\n"
  
end
