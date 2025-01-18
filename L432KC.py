
import time
import serial
import logging

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.INFO)


class L432KC():
    """
    Simple Class for serial USB communication with nucleoboard  L432KC 
    """
    __version__ = "v1.1.0"

    def __init__(self, port:str ="COM11", baudrate: int=115200, connect: bool=False, verbose: bool=False, timeout: float=0.2):
        super().__init__(port,baudrate)
        self.rxBufSize = 100
        self.txBufSize = 100
        self.last_incompl_line = ""
        self.state_of_connection = False
        self._port = port
        self._baudrate = baudrate
        self._timeout = timeout
        self.verbose = verbose
        self.id = {}

    def connect(self):
        '''  connect the computer to Device'''
        try:
            self._ser=serial.Serial(self._port, self._baudrate)
            self.deactivate_all()
            time.sleep(1)
            if self.verbose:
                logger.info("INFO: nucleoboard relay connected  ")


        except serial.serialutil.SerialException as P:
            logger.error("[ERROR] connection problem: ")
            time.sleep(1)
            logger.warning("[WARNING] reconnection... ")
            self._ser= serial.Serial(self._port, self._baudrate)
            self.deactivate_all()


    def is_connected(self):
        msg_ret = False
        try:
             self._query("*IDN?")
             msg_ret = True
        finally:
            if msg_ret:
                logger.info("INFO: nucleoboard relay is connected  ")

            else:
                logger.info("INFO: nucleoboard relay is not connected  ")

    def disconnect(self):
        try:
            self._ser.close()
        finally:
            logger.info("[WARNING] nucleoboard disconnected  ")

    def _serial_setBufferSize(self, rxBufSize, txBufSize):
        self.rxBufSize = rxBufSize
        self.txBufSize = txBufSize
        self._ser.set_buffer_size(rx_size=rxBufSize, tx_size=txBufSize)

    def _serial_write(self, string):
        """
        sends command to Nucleo Board
        """

        string = string + "\n"
        if ((self._ser.out_waiting < (self.txBufSize - (string.encode('utf-8')).__len__())) and (
                self._ser.out_waiting >= 0)):
            self._ser.write(string.encode('utf-8'))
            time.delay(0.1) # needed for startup sequence to generate enough deadtime for the arduino to read all commands
        else:
            logger.warning(
                "RX Buffer overflow! OutWaiting: {} Bytes | OutputBuffer Size: {} Bytes ".format(
                    self._ser.out_waiting,
                    self.txBufSize))

    def _empty_serial(self):
        """
        reads the current serial buffer and empties it
        """

        while self._ser.in_waiting > 0:
            self._ser.read_all()

    def _serial_read(self):
        """
        reads the current serial buffer
        """
        if self.rxBufSize > self._ser.in_waiting > 0:
            data_from_buffer = (self._ser.read(self._ser.in_waiting).decode('utf-8'))
            data = (self.last_incompl_line + data_from_buffer).split('\n')[0]
            self.last_incompl_line = ''
            return data


    def _query(self, msg: str) -> str:
        """
        Function to send a command to the device and read its answer.
        :param msg: str
        :return: str
        """
        try:
            self._serial_write(msg)
            time.delay(0.200)
        except serial.serialutil.SerialException as P:
            logger.error("[ERROR] connection lost: ")
            time.sleep(1)
            self.disconnect()
            logger.warning("[WARNING] reconnection... ")
            self.connect()
            self._serial_write(msg)
            time.delay(0.200)
        return self._serial_read()

    def get_IDN(self):
        """
        Get IDN of the Relay
        """
        msg_ret = self._query("*IDN?")
        logger.info(msg_ret)
        return msg_ret


    def set_pin(self,pin:int, state: int) -> bool:
        """
        set the state of a pin
        :param n: int
        :return: bool  True: relay NOT triggered (Positive voltage), False: Relais triggered (Negative voltage).
        """
        msg_ret = self._query("*IDN?")
        if self.verbose == True:
            logger.info(f"d: {msg_ret}  ")


    def _serial_disconnect(self):
        self._ser.close()
        logger.info("INFO: Connection to Device closed. ")

    def exemple_function(self, param1, param2):
        msg_ret = self._query(f"message{param1}{param2}")
        if self.verbose == True:
            logger.info(f"d: {msg_ret}  ")
        pass
