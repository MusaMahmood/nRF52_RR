package com.yeolabgt.mahmoodms.ecgrrdemo

import android.util.Log
import com.google.common.primitives.Bytes
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.util.*

/**
 * Created by mmahmood31 on 9/19/2017.
 * For Handling BLE incoming data packets.
 */

internal class DataChannel(var chEnabled: Boolean, MSBFirst: Boolean, //Classification:
                           var classificationBufferSize: Int) {
    var characteristicDataPacketBytes: ByteArray? = null
    var packetCounter: Short = 0
    var totalDataPointsReceived: Int = 0
    var dataBuffer: ByteArray? = null
    var classificationBuffer: DoubleArray
    private var classificationBufferFloats: FloatArray

    init {
        this.packetCounter = 0
        this.totalDataPointsReceived = 0
        this.classificationBuffer = DoubleArray(classificationBufferSize)
        this.classificationBufferFloats = FloatArray(classificationBufferSize)
        Companion.MSBFirst = MSBFirst
    }

    /**
     * If 'dataBuffer' is not null, concatenate new data using Guava lib
     * else: initialize dataBuffer with new data.
     *
     * @param newDataPacket new data packet received via BLE>
     */
    fun handleNewData(newDataPacket: ByteArray) {
        this.characteristicDataPacketBytes = newDataPacket
        if (this.dataBuffer != null) {
            this.dataBuffer = Bytes.concat(this.dataBuffer, newDataPacket)
        } else {
            this.dataBuffer = newDataPacket
        }
        for (i in 0 until newDataPacket.size / 4) {
            //Big Endian:
//            val bytes = arrayOf(newDataPacket[4 * i + 0], newDataPacket[4 * i + 1], newDataPacket[4 * i + 2], newDataPacket[4 * i + 3]).toByteArray()
            // Lil Endian:
            val bytes = arrayOf(newDataPacket[4 * i + 3], newDataPacket[4 * i + 2], newDataPacket[4 * i + 1], newDataPacket[4* i + 0]).toByteArray()
            addToBuffer(bytesToFloat(bytes).toDouble())
        }
        Log.e(TAG, "classificationBuffer: ${Arrays.toString(this.classificationBuffer)}")
        this.totalDataPointsReceived += newDataPacket.size / 4
        this.packetCounter++
    }

    private fun addToBuffer(a: Double) {
        if (this.classificationBufferSize > 0) {
            System.arraycopy(this.classificationBuffer, 1, this.classificationBuffer, 0, this.classificationBufferSize - 1) //shift backwards
            System.arraycopy(this.classificationBufferFloats, 1, this.classificationBufferFloats, 0, this.classificationBufferSize - 1) //shift backwards
            this.classificationBuffer[this.classificationBufferSize - 1] = a //add to front:
            this.classificationBufferFloats[this.classificationBufferSize - 1] = a.toFloat()
        }
    }

    fun resetBuffer() {
        this.dataBuffer = null
        this.packetCounter = 0
    }

    companion object {
        private var MSBFirst: Boolean = false

        private val TAG = DataChannel::class.java.simpleName

        fun bytesToDoubleMPUAccel(a1: Byte, a2: Byte): Double {
            val unsigned: Int = unsignedBytesToInt(a1, a2, MSBFirst)
            return unsignedToSigned16bit(unsigned).toDouble() / 32767.0 * 16.0
        }

        fun bytesToDoubleMPUGyro(a1: Byte, a2: Byte): Double {
            val unsigned: Int = unsignedBytesToInt(a1, a2, MSBFirst)
            return unsignedToSigned16bit(unsigned).toDouble() / 32767.0 * 4000.0
        }

        fun bytesToFloat32(a1: Byte, a2: Byte, a3: Byte): Float {
            val unsigned = unsignedBytesToInt(a1, a2, a3, MSBFirst)
            return unsignedToSigned24bit(unsigned).toFloat() / 8388607.0.toFloat() * 2.25.toFloat()
        }

        fun bytesToFloat32(a1: Byte, a2: Byte): Float {
            val unsigned = unsignedBytesToInt(a1, a2, MSBFirst)
            return unsignedToSigned16bit(unsigned).toFloat() / 32767.0.toFloat() * 2.25.toFloat()
        }

        fun bytesToDouble(a1: Byte, a2: Byte): Double {
            val unsigned = unsignedBytesToInt(a1, a2, MSBFirst)
            return unsignedToSigned16bit(unsigned).toDouble() / 32767.0 * 2.25
        }


        fun bytesToDouble(a1: Byte, a2: Byte, a3: Byte): Double {
            val unsigned = unsignedBytesToInt(a1, a2, a3, MSBFirst)
            return unsignedToSigned24bit(unsigned).toDouble() / 8388607.0 * 2.25
        }

        private fun unsignedToSigned16bit(unsigned: Int): Int {
            return if (unsigned and 0x8000 != 0)
                -1 * (0x8000 - (unsigned and 0x8000 - 1))
            else
                unsigned
        }

        fun bytesToFloat(byteArray: ByteArray): Float {
            return ByteBuffer.wrap(byteArray).order(ByteOrder.LITTLE_ENDIAN).float
        }

        fun bytesToFloat(b0: Byte, b1: Byte, b2: Byte, b3: Byte): Float {
            val mantissa = unsignedToSigned(unsignedByteToInt(b0)
                    + (unsignedByteToInt(b1) shl 8)
                    + (unsignedByteToInt(b2) shl 16), 24)
            return (mantissa * Math.pow(10.0, b3.toDouble())).toFloat()
        }

        /**
         * Convert an unsigned integer value to a two's-complement encoded
         * signed value.
         */
        private fun unsignedToSigned(unsigned: Int, size: Int): Int {
            var unsignedOut = unsigned
            if (unsignedOut and (1 shl size - 1) != 0) {
                unsignedOut = -1 * ((1 shl size - 1) - (unsignedOut and (1 shl size - 1) - 1))
            }
            return unsignedOut
        }

        private fun unsignedToSigned24bit(unsigned: Int): Int {
            return if (unsigned and 0x800000 != 0) -1 * (0x800000 - (unsigned and 0x800000 - 1))
            else unsigned
        }

        private fun unsignedBytesToInt(b0: Byte, b1: Byte, MSBFirst: Boolean): Int {
            return if (MSBFirst)
                (unsignedByteToInt(b0) shl 8) + unsignedByteToInt(b1)
            else
                unsignedByteToInt(b0) + (unsignedByteToInt(b1) shl 8)
        }

        private fun unsignedBytesToInt(b0: Byte, b1: Byte, b2: Byte, MSBFirst: Boolean): Int {
            return if (MSBFirst)
                (unsignedByteToInt(b0) shl 16) + (unsignedByteToInt(b1) shl 8) + unsignedByteToInt(b2)
            else
                unsignedByteToInt(b0) + (unsignedByteToInt(b1) shl 8) + (unsignedByteToInt(b2) shl 16)
        }

        private fun unsignedByteToInt(b: Byte): Int {
            return (b.toInt() and 0xFF)
        }

//        private fun unsignedToSigned(unsignedInt: Int, size: Int): Int {
//            var unsigned = unsignedInt
//            if (unsigned and (1 shl size - 1) != 0) unsigned = -1 * ((1 shl size - 1) - (unsigned and (1 shl size - 1) - 1))
//            return unsigned
//        }
    }

}
