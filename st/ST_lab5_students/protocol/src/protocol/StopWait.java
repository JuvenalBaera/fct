/*
 * Sistemas de Telecomunicacoes 
 *          2024/2025
 */
package protocol;

import simulator.AckFrameIF;
import simulator.DataFrameIF;
import terminal.Simulator;
import simulator.Frame;
import terminal.NetworkLayer;

/**
 * Protocol 3 : Stop and Wait protocol
 * 
 * @author 64932 (Put here your student number)
 */
public class StopWait extends Base_Protocol implements Callbacks {

    public StopWait(Simulator _sim, NetworkLayer _net) {
        super(_sim, _net);      // Calls the constructor of Base_Protocol

        // Initialize here all variables
        // ...
        next_frame_to_send = 0;
        frame_expected = 0;
    }
    
    private void send_data_frame(int seq, String packet){
        Frame data = Frame.new_Data_Frame(seq, prev_seq(frame_expected), null, packet);
        if(data != null){
            prevFrame = data;
            sim.to_physical_layer(data, false);
            sim.cancel_ack_timer();
        }
    }
    
    private void send_next_data_packet() {
        String packet = net.from_network_layer();
        if (packet != null) {
            send_data_frame(next_frame_to_send, packet);
            next_frame_to_send = next_seq(next_frame_to_send);
            sim.start_data_timer();
        }
    }

    /**
     * CALLBACK FUNCTION: handle the beginning of the simulation event
     * @param time current simulation time
     */
    @Override
    public void start_simulation(long time) {
        sim.Log("\nStop&Wait Protocol\n\n");
        //sim.Log("\nNot implemented yet\n\n"); 
        send_next_data_packet();
    }

    /**
     * CALLBACK FUNCTION: handle the end of Data frame transmission, start timer
     * @param time current simulation time
     * @param seq  sequence number of the Data frame transmitted
     */
    @Override
    public void handle_Data_end(long time, int seq) {
        // Do nothing
        sim.start_data_timer();
    }
    
    /**
     * CALLBACK FUNCTION: handle the timer event; retransmit failed frames
     * @param time current simulation time
     */
    @Override
    public void handle_Data_Timer(long time) {
        //sim.Log("handle_Data_Timer not implemented\n");
        sim.Log(time + ": Timeout, retransmitting frame " + prevFrame.seq() + "\n");
        sim.to_physical_layer(prevFrame, false);
        sim.start_data_timer();
    }
    
    /**
     * CALLBACK FUNCTION: handle the ack timer event; send ACK frame
     * @param time current simulation time
     */
    @Override
    public void handle_ack_Timer(long time) {
        //sim.Log("handle_ack_Timer not implemented\n");
        
        // Remember that you should not send an ACK while transmitting a DATA frame
        // You can check if a data frame is being transmitted using
        //           sim.is_sending_data()
        if(!sim.is_sending_data() && ack_pending){
            sim.Log(time + ": ACK timer expired. Sending ACK for frame " + prev_seq(frame_expected) + "\n");
            AckFrameIF ack = Frame.new_Ack_Frame(prev_seq(frame_expected), null);
            sim.to_physical_layer((Frame) ack, false);
            ack_pending = false;
        }
    }

    /**
     * CALLBACK FUNCTION: handle the reception of a frame from the physical layer
     * @param time current simulation time
     * @param frame frame received
     */
    @Override
    public void from_physical_layer(long time, Frame frame) {
        //sim.Log("from_physical_layer not implemented\n");
        // Receiver: Recebe DATA Frame
        if(frame.kind() == Frame.DATA_FRAME){
            DataFrameIF dframe = frame;
            if(dframe.seq() == frame_expected){
                if(net.to_network_layer(dframe.info())){
                    frame_expected = next_seq(frame_expected);
                    ack_pending = true;
                    sim.start_ack_timer(); // Iniciar o temporizador para ACK
                }
            }
            else{
                ack_pending = true;
                sim.start_ack_timer();
            }
        }
        
        // Sender: recebe ACK
        if(frame.kind() == Frame.ACK_FRAME){
            AckFrameIF aframe = frame;
            sim.Log(time + ": Received ACK for frame " + aframe.ack() + "\n");
            if(aframe.ack() == prev_seq(next_frame_to_send)){
                sim.cancel_data_timer();
                send_next_data_packet();
            }
        }
    }

    /**
     * CALLBACK FUNCTION: handle the end of the simulation
     * @param time current simulation time
     */
    @Override
    public void end_simulation(long time) {
        sim.Log("Stopping simulation\n");
    }
    
    
    /* Variables */
    private int next_frame_to_send;
    private int frame_expected;
    private Frame prevFrame;
    private boolean ack_pending;
    /**
     * Reference to the simulator (Terminal), to get the configuration and send commands
     */
    //final Simulator sim;  -  Inherited from Base_Protocol
    
    /**
     * Reference to the network layer, to send a receive packets
     */
    //final NetworkLayer net;    -  Inherited from Base_Protocol
    
}
