/*
 * Sistemas de Telecomunicacoes 
 *          2024/2025
 */
package simulator;

import java.util.StringTokenizer;
import simulator.SequenceNumbers;


/**
 * Defines the frames exchanged between the terminal protocol objects and the 
 * channel. Implements methods to create new objects, to serialize and deserialize.
 * 
 * @author lflb@fct.unl.pt
 */
public class Frame implements DataFrameIF, AckFrameIF {
    
    /**
     * Undefined (uninitialized event)
     */
    public static final int UNDEFINED_FRAME = 0;
    
    /**
     * Data frame
     */
    public static final int DATA_FRAME = 21;
    
    /**
     * ACK frame
     */
    public static final int ACK_FRAME = 22;
        
    /**
     * Undefined sequence number; it must be 0 or above
     */
    public static final int UNDEFINED_SEQ = -1;

    /**
     * Undefined buffer size. The receiving buffer size is unknown
     */
    public static final int UNDEFINED_BUF_SIZE = -1;
    
    /**
     * Maximum length of the selective ACK vector
     */
    public static final int MAX_ACKVEC_LENGTH = 32;
    
    /**
     * Maximum length of the data information string
     */
    public static final int MAX_INFO_LENGTH = 100;

    /**
     * Constructor
     */
    public Frame() {
        kind = UNDEFINED_FRAME;
        info = null;
        seq = UNDEFINED_SEQ;
        ack = UNDEFINED_SEQ;
        ackvector = null;
        sendTime = Event.UNDEF_TIME;
        recvTime = Event.UNDEF_TIME;
    }

    /**
     * Resets the frame contents to UNDEFINED_FRAME
     */
    private void reset_frame() {
        kind = UNDEFINED_FRAME;
        info = null;
        seq = UNDEFINED_SEQ;
        ack = UNDEFINED_SEQ;
        ackvector = null;
        sendTime = Event.UNDEF_TIME;
        recvTime = Event.UNDEF_TIME;
    }

    
    /* Static methods to create new frame object instances */
    
    /**
     * Creates a new instance (object) of a Data frame 
     * @param seq sequence number
     * @param ack acknowledgment number
     * @param info packet transmitted
     * @param ackvector vector with sequence numbers received out of order
     * @return the frame object created
     */
    public static Frame new_Data_Frame(int seq, int ack, int[] ackvector, String info) {
        Frame frame= new Frame();
        frame.set_DATA_frame(seq, ack, ackvector, info);
        return frame;
    }
    
    /**
     * Creates a new instance (object) of an Ack frame
     * @param ack acknowledgment number
     * @param ackvector vector with sequence numbers received out of order
     * @return the frame object created
     */
    public static Frame new_Ack_Frame(int ack, int[] ackvector) {
        Frame frame= new Frame();
        frame.set_ACK_frame(ack, ackvector);
        return frame;
    }

    /* Methods to read the frame fields' contents */
    /* They should be used through variables of Interface classes DataFrameIF, AckFrameIF and NakFrameIF */ 
        
    /**
     * Get the kind of the frame object
     * @return the kind of the frame
     */
    @Override
    public int kind() {
        return kind;
    }
    
    /**
     * Get the sequence number (valid for DATA_FRAME kind)
     * @return the sequence number
     */
    @Override
    public int seq() {
        return seq;
    }
    
    /**
     * Set the sequence number (valid for DATA_FRAME kind)
     * @param seq new sequence number
     * @return the previous sequence number value
     */
    public int set_seq(int seq) {
        int bak= this.seq;
        this.seq= seq;
        return bak;
    } 
    
    /**
     * Get the acknowledgement number
     * @return the acknowledgement number
     */
    @Override
    public int ack() {
        return ack;
    }

    /**
     * Set the acknowledgement number value (for DATA_FRAME and ACK_FRAME)
     * @param ack new acknowledgement number
     * @return the previous acknowledgement number value
     */
    public int set_ack(int ack) {
        int bak= this.ack;
        this.ack= ack;
        return bak;
        
    }
        
    /**
     * Get the acknowledgement vector, with frames received after ack
     * @return the acknowledgement vector
     */
    public int[] ackvec() {
        return ackvector;
    }

    /**
     * Set the acknowledgment vector value - not used
     * @param ackvector acknowledgment vector
     * @return true if successful, false otherwise
     */
    public boolean set_ackvec(int[] ackvector) {
        if ((ackvector == null) || (ackvector.length > MAX_ACKVEC_LENGTH)) {
            return false;
        }
        this.ackvector = ackvector;
        return true;
    }

    /**
     * Get the information of a DATA_FRAME
     * @return the information carried
     */
    @Override
    public String info() {
        return info;
    }
    
    /**
     * Set the information for a DATA_FRAME
     * @param info the information carried
     * @return the previous information carried
     */
    public String set_info(String info) {
        String bak= this.info;
        this.info= info;
        return bak;           
    }

    /**
     * Get the initial sending time of the frame
     * @return the sending time, or Event.UNDEF_TIME
     */
    public long snd_time() {
        return this.sendTime;
    }

    /**
     * Get the reception time of the frame
     * @return the reception time, or Event.UNDEF_TIME
     */
    public long rcv_time() {
        return this.recvTime;
    }

    /**
     * Test if the event is undefined
     * @return true if is undefined, false otherwise
     */
    boolean is_undef() {
        return kind == UNDEFINED_FRAME;
    }
    
    /**
     * Compares local ackvec with vec's contents
     * @param vec ackvector
     * @return true if equal,false otherwise
     */
    public boolean equal_ackvec(int[] vec) {
        if ((this.ackvector == null) && (vec == null))
            return true;
        if ((this.ackvector != null) && (vec != null)) {
             if (this.ackvector.length != vec.length)
                return false;
            for (int i= 0; i<ackvector.length; i++)
                if (ackvector[i] != vec[i])
                    return false;
            return true;
        } else
            return false;
    }
    
     /**
     * Validate the ack and ackvec with vec's contents
     * @param max_seq maximum sequence number
     * @return true if equal,false otherwise
     */
    public boolean valid_ackvec(int max_seq) {
        if (this.ackvector == null)
            return true;
        int total_range= 0;
        for (int i= 0; i<this.ackvector.length; i++) {
            if (this.ackvector[i] == this.ack)
                // the ack value cannot exists in ackvec
                return false;
            if (i==0)
                total_range += SequenceNumbers.diff_seq(this.ack, this.ackvector[i], max_seq);
            else
                total_range += SequenceNumbers.diff_seq(this.ackvector[i-1], this.ackvector[i], max_seq);    
        }
        return total_range <= (max_seq+1)/2;    // The maximum receiver window size is half of the range for selective repeat
    }
    
   /**
     * Test if the frames contents are equal, ignoring times 
     * @param f other frame
     * @return true if equal
     */
    public boolean equal_content(Frame f) {
        if ((f.kind != this.kind) || (this.kind == Frame.UNDEFINED_FRAME))
            return false;
        switch (this.kind()) {
            case Frame.DATA_FRAME:
                if (f.seq != this.seq)
                    return false;
                if (f.info==null || this.info==null || !f.info.equals(this.info))
                    return false;
                // continue to the next case!
            case Frame.ACK_FRAME:
                if (f.ack != this.ack)
                    return false;
                return equal_ackvec(f.ackvector);
                
            default:
                return false;
        }

    }

    /**
     * Get a string with the kind of the frame
     * @return string with the kind of frame
     */
    public String kindString() {
        String str;
        switch (kind) {
            case UNDEFINED_FRAME:
                str = "UNDEFINED";
                break;
            case DATA_FRAME:
                str = "DATA";
                break;
            case ACK_FRAME:
                str = "ACK";
                break;
            default:
                str = "INVALID";
        }
        return str;
    }

    /**
     * Returns a string with the frame object's contents
     * @return string with the frame object's contents
     */
    @Override
    public String toString() {
        String str = kindString();
        if (kind == DATA_FRAME) {
            str += " " + (seq == UNDEFINED_SEQ ? "undef seq" : seq);
        }
        if (kind == DATA_FRAME || kind == ACK_FRAME /*|| kind == NAK_FRAME*/) {
            str += " " + (ack == UNDEFINED_SEQ ? "undef ack" : ack);
        }
        if (ackvector != null) {
            str += " ackvec(";
            for (int i = 0; i < ackvector.length; i++) {
                str += ((i == 0) ? "" : " ") + ackvector[i];
            }
            str += ")";
        }
        // ...
        return str;
    }

    /**
     * Used with DATA_FRAME frames to set the fields values
     * @param seq sequence number
     * @param ack acknowledgement number
     * @param ackvector vector with sequence numbers received out of order
     * @param info packet information
     * @return true if successful, false otherwise
     */
    private boolean set_DATA_frame(int seq, int ack, int[] ackvector, String info) {
        if ((seq <= UNDEFINED_SEQ) || (ack <= UNDEFINED_SEQ) || (info == null)
                || info.isEmpty() || (info.length() > MAX_INFO_LENGTH)) {
            return false;
        }
        kind = DATA_FRAME;
        this.seq = seq;
        this.ack = ack;
        this.info = info;
        this.set_ackvec(ackvector);
        return true;
    }

    /**
     * Used with ACK_FRAME frames to set the fields values
     * @param ack acknowledgement number
     * @param ackvector vector with sequence numbers received out of order
     * @return true if successful, false otherwise
     */
    private boolean set_ACK_frame(int ack, int[] ackvector) {
        if (ack <= UNDEFINED_SEQ) {
            return false;
        }
        kind = ACK_FRAME;
        this.ack = ack;
        this.set_ackvec(ackvector);
        return true;
    }

    /**
     * Set the frame sending time
     * @param sendTime initial sending time
     * @return true if successful, false otherwise
     */
    public boolean set_sendTime(long sendTime) {
        if ((sendTime != Event.UNDEF_TIME) && (sendTime < 0)) {
            return false;
        }
        this.sendTime = sendTime;
        return true;
    }

    /**
     * Set the frame reception time
     * @param recvTime reception time
     * @return true if successful, false otherwise
     */
    public boolean set_recvTime(long recvTime) {
        if ((recvTime != Event.UNDEF_TIME) && (recvTime < 0) || (sendTime >= recvTime)) {
            return false;
        }
        this.recvTime = recvTime;
        return true;
    }

    
    /**
     * Prepares a string with the frame contents, serializing the object
     * @return the string, or null if error
     */
    public String frame_to_str() {
        if (kind == UNDEFINED_FRAME) {
            return null;
        }
        String str = "";

        // Set initial header 
        switch (kind) {
            case DATA_FRAME:
                str = "DATA " + seq + " " + ack;
                break;
            case ACK_FRAME:
                str = "ACK " + ack;
                break;
        }
        // Write ACK vector
        if (ackvector != null) {
            str += " ACKVEC " + ackvector.length;
            for (int i = 0; i < ackvector.length; i++) {
                str += " " + ackvector[i];
            }
        }

        // Write sendTime
        if (sendTime != Event.UNDEF_TIME) {
            str += " SNDTIME " + sendTime;
        }

        // Write sendTime
        if (recvTime != Event.UNDEF_TIME) {
            str += " RCVTIME " + recvTime;
        }

        // Write DATA
        if (info != null) {
            str += " INFO " + info.length() + " " + info;
        }

        return str;
    }

    /**
     * Decodes the contents of a string to the frame, desirealizing it
     * @param line - string with the frame's contents
     * @param log - Logging object
     * @return true if decoded successfully, false otherwise
     */
    public boolean str_to_frame(String line, Log log) {
        if (line == null) {
            return false;
        }
        StringTokenizer st = new StringTokenizer(line);
        String cmd = null;

        try {
            while (st.hasMoreTokens()) {
                cmd = st.nextToken();
                switch (cmd) {
                    case "DATA":
                        if (kind != UNDEFINED_FRAME) {
                            log.Log("Can have only one DATA,ACK or NAK\n");
                            reset_frame();
                            return false;
                        }   
                        kind = DATA_FRAME;
                        if (st.countTokens() < 3) {
                            log.Log("Received DATA without enough parameters\n");
                            reset_frame();
                            return false;
                        }   
                        seq = Event.parseInt(st.nextToken());
                        ack = Event.parseInt(st.nextToken());
                        break;
                    case "ACK":
                        if (kind != UNDEFINED_FRAME) {
                            log.Log("Can have only one DATA,ACK or NAK\n");
                            reset_frame();
                            return false;
                        }   
                        kind = ACK_FRAME;
                        if (st.countTokens() < 2) {
                            log.Log("Received ACK without enough parameters\n");
                            reset_frame();
                            return false;
                        }   
                        ack = Event.parseInt(st.nextToken());
                        break;
                    case "SNDTIME":
                        if (st.countTokens() < 1) {
                            log.Log("Received SNDTIME without enough parameters\n");
                            reset_frame();
                            return false;
                        }   
                        sendTime = Event.parseLong(st.nextToken());
                        break;
                    case "RCVTIME":
                        if (st.countTokens() < 1) {
                            log.Log("Received RCVTIME without enough parameters\n");
                            reset_frame();
                            return false;
                        }   
                        recvTime = Event.parseLong(st.nextToken());
                        break;
                    case"ACKVEC":
                        if (st.hasMoreTokens()) {
                            int len = Event.parseInt(st.nextToken());
                            if (len < 1 || len > MAX_ACKVEC_LENGTH) {
                                log.Log("Received ACKVEC with invalid vector length\n");
                                reset_frame();
                                return false;
                            }
                            if (st.countTokens() < len) {
                                log.Log("Received ACKVEC with insufficient number of vector elements\n");
                                reset_frame();
                                return false;
                            }
                            ackvector = new int[len];
                            for (int i = 0; i < len; i++) {
                                ackvector[i] = Event.parseInt(st.nextToken());
                            }
                        } else {
                            log.Log("Received ACKVEC without enough parameters\n");
                            reset_frame();
                            return false;
                        }
                        break;
                    case "INFO":
                        if (st.hasMoreTokens()) {
                            int len = Event.parseInt(st.nextToken());
                            if (len < 1 || len > MAX_INFO_LENGTH) {
                                log.Log("Received DATA with invalid data length\n");
                                reset_frame();
                                return false;
                            }
                            info = st.nextToken();
                            if (info.length() != len) {
                                log.Log("Received DATA with invalid length (" + len + "!=" + info.length() + ")\n");
                                reset_frame();
                                return false;
                            }
                        } else {
                            log.Log("Received INFO without enough parameters\n");
                            reset_frame();
                            return false;
                        }   
                        break;
                    default:
                        log.Log("Received invalid token '" + cmd + "'\n");
                        reset_frame();
                        return false;
                }
            }
            return true;
        } catch (NumberFormatException ne) {
            log.Log("Invalid number in " + (cmd == null ? "" : cmd) + " element\n");
            reset_frame();
            return false;
        } catch (Exception e) {
            log.Log("Exception in " + (cmd == null ? "" : cmd) + " element: " + e + "\n");
            reset_frame();
            return false;
        }
    }
    
    
    /* Frame fields */
    
    /**
     * Frame kind - can be: UNDEFINED_PCKT or DATA_PCKT or ACK_PCKT
     */
    private int kind;
    
    /**
     * Data - only used for DATA packets
     */
    private String info;
    
    /**
     * Sequence number - only used for DATA packets
     */
    private int seq;
    
    /**
     * Acknowledge number - for DATA, ACK and NAK packets; it defines the 
     * sequence number of the last DATA frame successfully received for DATA and 
     * ACK; if defines the missing DATA frame for NAK packets
     */
    private int ack;
    
    /**
     * Acknowledge vector, with packets received above 'ack' - for DATA and ACK
     * packets
     */
    private int[] ackvector;
    
    /**
     * Frame sending time
     */
    private long sendTime;
    
    /**
     * Frame reception time
     */
    private long recvTime;
}
