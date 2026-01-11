#include <zmq.hpp>
#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <cstdlib>

// A way to pack an array of 4 chars into a single 32-bit unsigned integer.
// Packs in big endian order.
uint32_t serialize_char_into_uint32(const unsigned char* data) {
  uint32_t serialized_data = 0;
  
  
  serialized_data |= static_cast<uint32_t>(data[0]) << 24;
  serialized_data |= static_cast<uint32_t>(data[1]) << 16;
  serialized_data |= static_cast<uint32_t>(data[2]) << 8;
  serialized_data |= static_cast<uint32_t>(data[3]);

  return serialized_data;
}

void listener_loop(zmq::socket_t& sub){
  while (true) {
    zmq::message_t received_message;
    zmq::recv_result_t received_data = sub.recv(received_message, zmq::recv_flags::none);
    
    if(!received_data.has_value()) {
      continue;
    }

    std::cout << "RECEIVED MESSAGE\nData: " << received_message.to_string() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
}

int main(int argc, char* argv[]) {
  if (argc <= 0) {
    std::cout << "Input an IP to send packets to!";
    return 0;
  }
  unsigned char message[4] = {'T', 'E', 'S', 'T'};
  std::string target_ip = argv[1];
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REP);
  socket.bind("tcp://" + target_ip + ":5555");
  
  std::cout << "Sending to " << target_ip;
  std::cout << "Press Esc or Ctrl+C to exit\nPress Space to send a message!";
  bool space_held_down = false;
  while (true) {
        uint32_t serialized_message = serialize_char_into_uint32(message);
        zmq::message_t send_message(4); 
        memcpy(send_message.data(), &serialized_message, 4);

        if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !space_held_down) {
            space_held_down = true;
            std::cout << "Sending" << std::endl;
            socket.send(send_message, zmq::send_flags::none);

        }
        if (!(GetAsyncKeyState(VK_SPACE) & 0x8000) && space_held_down) {
          space_held_down = false;
        }

        // Check if 'Esc' key (VK_ESCAPE) is pressed to exit the loop
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            std::cout << "Esc pressed. Exiting." << std::endl;
            break;
        }
        
        // Small delay to prevent excessive CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
