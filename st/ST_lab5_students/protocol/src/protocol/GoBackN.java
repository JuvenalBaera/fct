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
 * Protocol 4 : Go-back-N protocol with a single timer
 *
 * @author 64932 (Put here your student number)
 */
public class GoBackN extends Base_Protocol implements Callbacks {

    public GoBackN(Simulator _sim, NetworkLayer _net) {
        super(_sim, _net);      // Calls the constructor of Base_Protocol

        // Initialize here all variables
        // ...
    }

    /**
     * CALLBACK FUNCTION: handle the beginning of the simulation event
     *
     * @param time current simulation time
     */
    @Override
    public void start_simulation(long time) {
        sim.Log("\nGo-Back-N Protocol\n\n");
        max_seq = sim.get_max_sequence(); // geralmente 7
        buffer = new String[max_seq + 1];

        next_frame_to_send = 0;
        ack_expected = 0;
        frame_expected = 0;
        nbuffered = 0;

        send_next_data_packet();

        //sim.Log("\nNot implemented yet\n\n");
    }
    
    private void send_next_data_packet(){
        if(nbuffered < max_seq){ // window is full??
            if(!sim.is_sending_data()){
                String packet = net.from_network_layer();
                if(packet != null){
                    buffer[next_frame_to_send] = packet;
                    Frame data = Frame.new_Data_Frame(next_frame_to_send, prev_seq(frame_expected), null, packet);
                    sim.to_physical_layer(data, false);

                    if(ack_expected == next_frame_to_send){
                        sim.start_data_timer(); // start oldest timer
                    }

                    next_frame_to_send = next_seq(next_frame_to_send);
                    nbuffered++;
                }
            }
            else{
                sim.Log("Is sending another packet: " + ack_expected + "\n");
            }
        }
    }

    /**
     * CALLBACK FUNCTION: handle the end of Data frame transmission, start timer
     * and send next until reaching the end of the sending window.
     *
     * @param time current simulation time
     * @param seq sequence number of the Data frame transmitted
     */
    @Override
    public void handle_Data_end(long time, int seq) {
        // sim.Log("handle_Data_end not implemented\n");
        if(resend_seq != -1){
            resend_seq = next_seq(resend_seq);
            
            // Ainda está dentro da janela??
            if(between(ack_expected, resend_seq, next_frame_to_send)){
                if(!sim.is_sending_data()){
                    Frame frame = Frame.new_Data_Frame(resend_seq, prev_seq(frame_expected), null, buffer[resend_seq]);
                    sim.to_physical_layer(frame, false);
                }
            }
            else{
                resend_seq = -1;
                sim.start_data_timer();
                send_next_data_packet();
            }
        }
        else{
            send_next_data_packet();
        }
    }

    /**
     * CALLBACK FUNCTION: handle the timer event; retransmit failed frames.
     *
     * @param time current simulation time
     */
    @Override
    public void handle_Data_Timer(long time) {
        // sim.Log("handle_Data_Timer not implemented\n");
        sim.Log(time + ": Timeout. Resending from frame " + ack_expected + "\n");
        
        resend_seq = ack_expected;
        
        if(!sim.is_sending_data()){
            Frame frame = Frame.new_Data_Frame(resend_seq, prev_seq(frame_expected), null, buffer[resend_seq]);
            sim.to_physical_layer(frame, false);
        }
    }

    /**
     * CALLBACK FUNCTION: handle the ack timer event; send ACK frame
     *
     * @param time current simulation time
     */
    @Override
    public void handle_ack_Timer(long time) {
        //sim.Log("handle_ack_Timer not implemented\n");
    }

    /**
     * CALLBACK FUNCTION: handle the reception of a frame from the physical
     * layer
     *
     * @param time current simulation time
     * @param frame frame received
     */
    @Override
    public void from_physical_layer(long time, Frame frame) {
        //sim.Log("from_physical_layer not implemented\n");
        if(frame.kind() == Frame.ACK_FRAME){
            AckFrameIF aframe = frame;
            sim.Log(time + ": Received ACK " + aframe.ack() + "\n");
            
            while(between(ack_expected, aframe.ack(), next_frame_to_send)){
                nbuffered--;
                ack_expected = next_seq(ack_expected);
            }
            
            if(nbuffered > 0) sim.start_data_timer();
            else sim.cancel_data_timer();
            
            send_next_data_packet();
        }
        
        if(frame.kind() == Frame.DATA_FRAME){
            DataFrameIF dframe = frame;
            
            if(dframe.seq() == frame_expected){
                if(net.to_network_layer(dframe.info())){
                    frame_expected = next_seq(frame_expected);
                }
            }
            
            AckFrameIF ack = Frame.new_Ack_Frame(prev_seq(frame_expected), null);
            sim.to_physical_layer((Frame) ack, false);
        }
    }

    /**
     * CALLBACK FUNCTION: handle the end of the simulation
     *
     * @param time current simulation time
     */
    @Override
    public void end_simulation(long time) {
        sim.Log("Stopping simulation\n");
    }

    /* Variables */
    private int resend_seq = -1; // Controle de retransmissão
    private int next_frame_to_send; // próximo número de sequência a ser usado
    private int ack_expected;       // menor número de sequência não confirmado
    private int frame_expected;     // usado no receptor para confirmar sequências
    private int max_seq;            // sim.get_max_sequence()
    private int nbuffered;          // número de frames não confirmados
    private String[] buffer;        // buffer circular de pacotes para retransmissão

    /**
     * Reference to the simulator (Terminal), to get the configuration and send
     * commands
     */
    //final Simulator sim;  -  Inherited from Base_Protocol
    /**
     * Reference to the network layer, to send a receive packets
     */
    //final NetworkLayer net;    -  Inherited from Base_Protocol

}