#ifndef __MACH_IRQS_H__
#define __MACH_IRQS_H__

#include <mach/platform.h>


#define IRQ_ARMCTRL_START     0
#define IRQ_TIMER0            (IRQ_ARMCTRL_START + INTERRUPT_TIMER0)
#define IRQ_TIMER1            (IRQ_ARMCTRL_START + INTERRUPT_TIMER1)
#define IRQ_TIMER2            (IRQ_ARMCTRL_START + INTERRUPT_TIMER2)
#define IRQ_TIMER3            (IRQ_ARMCTRL_START + INTERRUPT_TIMER3)
#define IRQ_CODEC0            (IRQ_ARMCTRL_START + INTERRUPT_CODEC0)
#define IRQ_CODEC1            (IRQ_ARMCTRL_START + INTERRUPT_CODEC1)
#define IRQ_CODEC2            (IRQ_ARMCTRL_START + INTERRUPT_CODEC2)
#define IRQ_JPEG              (IRQ_ARMCTRL_START + INTERRUPT_JPEG)
#define IRQ_ISP               (IRQ_ARMCTRL_START + INTERRUPT_ISP)
#define IRQ_USB               (IRQ_ARMCTRL_START + INTERRUPT_USB)
#define IRQ_3D                (IRQ_ARMCTRL_START + INTERRUPT_3D)
#define IRQ_TRANSPOSER        (IRQ_ARMCTRL_START + INTERRUPT_TRANSPOSER)
#define IRQ_MULTICORESYNC0    (IRQ_ARMCTRL_START + INTERRUPT_MULTICORESYNC0)
#define IRQ_MULTICORESYNC1    (IRQ_ARMCTRL_START + INTERRUPT_MULTICORESYNC1)
#define IRQ_MULTICORESYNC2    (IRQ_ARMCTRL_START + INTERRUPT_MULTICORESYNC2)
#define IRQ_MULTICORESYNC3    (IRQ_ARMCTRL_START + INTERRUPT_MULTICORESYNC3)
#define IRQ_DMA0              (IRQ_ARMCTRL_START + INTERRUPT_DMA0)
#define IRQ_DMA1              (IRQ_ARMCTRL_START + INTERRUPT_DMA1)
#define IRQ_DMA2              (IRQ_ARMCTRL_START + INTERRUPT_DMA2)
#define IRQ_DMA3              (IRQ_ARMCTRL_START + INTERRUPT_DMA3)
#define IRQ_DMA4              (IRQ_ARMCTRL_START + INTERRUPT_DMA4)
#define IRQ_DMA5              (IRQ_ARMCTRL_START + INTERRUPT_DMA5)
#define IRQ_DMA6              (IRQ_ARMCTRL_START + INTERRUPT_DMA6)
#define IRQ_DMA7              (IRQ_ARMCTRL_START + INTERRUPT_DMA7)
#define IRQ_DMA8              (IRQ_ARMCTRL_START + INTERRUPT_DMA8)
#define IRQ_DMA9              (IRQ_ARMCTRL_START + INTERRUPT_DMA9)
#define IRQ_DMA10             (IRQ_ARMCTRL_START + INTERRUPT_DMA10)
#define IRQ_DMA11             (IRQ_ARMCTRL_START + INTERRUPT_DMA11)
#define IRQ_DMA12             (IRQ_ARMCTRL_START + INTERRUPT_DMA12)
#define IRQ_AUX               (IRQ_ARMCTRL_START + INTERRUPT_AUX)
#define IRQ_ARM               (IRQ_ARMCTRL_START + INTERRUPT_ARM)
#define IRQ_VPUDMA            (IRQ_ARMCTRL_START + INTERRUPT_VPUDMA)
#define IRQ_HOSTPORT          (IRQ_ARMCTRL_START + INTERRUPT_HOSTPORT)
#define IRQ_VIDEOSCALER       (IRQ_ARMCTRL_START + INTERRUPT_VIDEOSCALER)
#define IRQ_CCP2TX            (IRQ_ARMCTRL_START + INTERRUPT_CCP2TX)
#define IRQ_SDC               (IRQ_ARMCTRL_START + INTERRUPT_SDC)
#define IRQ_DSI0              (IRQ_ARMCTRL_START + INTERRUPT_DSI0)
#define IRQ_AVE               (IRQ_ARMCTRL_START + INTERRUPT_AVE)
#define IRQ_CAM0              (IRQ_ARMCTRL_START + INTERRUPT_CAM0)
#define IRQ_CAM1              (IRQ_ARMCTRL_START + INTERRUPT_CAM1)
#define IRQ_HDMI0             (IRQ_ARMCTRL_START + INTERRUPT_HDMI0)
#define IRQ_HDMI1             (IRQ_ARMCTRL_START + INTERRUPT_HDMI1)
#define IRQ_PIXELVALVE1       (IRQ_ARMCTRL_START + INTERRUPT_PIXELVALVE1)
#define IRQ_I2CSPISLV         (IRQ_ARMCTRL_START + INTERRUPT_I2CSPISLV)
#define IRQ_DSI1              (IRQ_ARMCTRL_START + INTERRUPT_DSI1)
#define IRQ_PWA0              (IRQ_ARMCTRL_START + INTERRUPT_PWA0)
#define IRQ_PWA1              (IRQ_ARMCTRL_START + INTERRUPT_PWA1)
#define IRQ_CPR               (IRQ_ARMCTRL_START + INTERRUPT_CPR)
#define IRQ_SMI               (IRQ_ARMCTRL_START + INTERRUPT_SMI)
#define IRQ_GPIO0             (IRQ_ARMCTRL_START + INTERRUPT_GPIO0)
#define IRQ_GPIO1             (IRQ_ARMCTRL_START + INTERRUPT_GPIO1)
#define IRQ_GPIO2             (IRQ_ARMCTRL_START + INTERRUPT_GPIO2)
#define IRQ_GPIO3             (IRQ_ARMCTRL_START + INTERRUPT_GPIO3)
#define IRQ_I2C               (IRQ_ARMCTRL_START + INTERRUPT_I2C)
#define IRQ_SPI               (IRQ_ARMCTRL_START + INTERRUPT_SPI)
#define IRQ_I2SPCM            (IRQ_ARMCTRL_START + INTERRUPT_I2SPCM)
#define IRQ_SDIO              (IRQ_ARMCTRL_START + INTERRUPT_SDIO)
#define IRQ_UART              (IRQ_ARMCTRL_START + INTERRUPT_UART)
#define IRQ_SLIMBUS           (IRQ_ARMCTRL_START + INTERRUPT_SLIMBUS)
#define IRQ_VEC               (IRQ_ARMCTRL_START + INTERRUPT_VEC)
#define IRQ_CPG               (IRQ_ARMCTRL_START + INTERRUPT_CPG)
#define IRQ_RNG               (IRQ_ARMCTRL_START + INTERRUPT_RNG)
#define IRQ_ARASANSDIO        (IRQ_ARMCTRL_START + INTERRUPT_ARASANSDIO)
#define IRQ_AVSPMON           (IRQ_ARMCTRL_START + INTERRUPT_AVSPMON)

#define IRQ_ARM_TIMER         (IRQ_ARMCTRL_START + INTERRUPT_ARM_TIMER)
#define IRQ_ARM_MAILBOX       (IRQ_ARMCTRL_START + INTERRUPT_ARM_MAILBOX)
#define IRQ_ARM_DOORBELL_0    (IRQ_ARMCTRL_START + INTERRUPT_ARM_DOORBELL_0)
#define IRQ_ARM_DOORBELL_1    (IRQ_ARMCTRL_START + INTERRUPT_ARM_DOORBELL_1)
#define IRQ_VPU0_HALTED       (IRQ_ARMCTRL_START + INTERRUPT_VPU0_HALTED)
#define IRQ_VPU1_HALTED       (IRQ_ARMCTRL_START + INTERRUPT_VPU1_HALTED)
#define IRQ_ILLEGAL_TYPE0     (IRQ_ARMCTRL_START + INTERRUPT_ILLEGAL_TYPE0)
#define IRQ_ILLEGAL_TYPE1     (IRQ_ARMCTRL_START + INTERRUPT_ILLEGAL_TYPE1)
#define IRQ_PENDING1          (IRQ_ARMCTRL_START + INTERRUPT_PENDING1)
#define IRQ_PENDING2          (IRQ_ARMCTRL_START + INTERRUPT_PENDING2)

#define FIQ_START             HARD_IRQS

/*
 *  FIQ interrupts definitions are the same as the INT definitions.
 */
#define FIQ_TIMER0            (FIQ_START+INTERRUPT_TIMER0)
#define FIQ_TIMER1            (FIQ_START+INTERRUPT_TIMER1)
#define FIQ_TIMER2            (FIQ_START+INTERRUPT_TIMER2)
#define FIQ_TIMER3            (FIQ_START+INTERRUPT_TIMER3)
#define FIQ_CODEC0            (FIQ_START+INTERRUPT_CODEC0)
#define FIQ_CODEC1            (FIQ_START+INTERRUPT_CODEC1)
#define FIQ_CODEC2            (FIQ_START+INTERRUPT_CODEC2)
#define FIQ_JPEG              (FIQ_START+INTERRUPT_JPEG)
#define FIQ_ISP               (FIQ_START+INTERRUPT_ISP)
#define FIQ_USB               (FIQ_START+INTERRUPT_USB)
#define FIQ_3D                (FIQ_START+INTERRUPT_3D)
#define FIQ_TRANSPOSER        (FIQ_START+INTERRUPT_TRANSPOSER)
#define FIQ_MULTICORESYNC0    (FIQ_START+INTERRUPT_MULTICORESYNC0)
#define FIQ_MULTICORESYNC1    (FIQ_START+INTERRUPT_MULTICORESYNC1)
#define FIQ_MULTICORESYNC2    (FIQ_START+INTERRUPT_MULTICORESYNC2)
#define FIQ_MULTICORESYNC3    (FIQ_START+INTERRUPT_MULTICORESYNC3)
#define FIQ_DMA0              (FIQ_START+INTERRUPT_DMA0)
#define FIQ_DMA1              (FIQ_START+INTERRUPT_DMA1)
#define FIQ_DMA2              (FIQ_START+INTERRUPT_DMA2)
#define FIQ_DMA3              (FIQ_START+INTERRUPT_DMA3)
#define FIQ_DMA4              (FIQ_START+INTERRUPT_DMA4)
#define FIQ_DMA5              (FIQ_START+INTERRUPT_DMA5)
#define FIQ_DMA6              (FIQ_START+INTERRUPT_DMA6)
#define FIQ_DMA7              (FIQ_START+INTERRUPT_DMA7)
#define FIQ_DMA8              (FIQ_START+INTERRUPT_DMA8)
#define FIQ_DMA9              (FIQ_START+INTERRUPT_DMA9)
#define FIQ_DMA10             (FIQ_START+INTERRUPT_DMA10)
#define FIQ_DMA11             (FIQ_START+INTERRUPT_DMA11)
#define FIQ_DMA12             (FIQ_START+INTERRUPT_DMA12)
#define FIQ_AUX               (FIQ_START+INTERRUPT_AUX)
#define FIQ_ARM               (FIQ_START+INTERRUPT_ARM)
#define FIQ_VPUDMA            (FIQ_START+INTERRUPT_VPUDMA)
#define FIQ_HOSTPORT          (FIQ_START+INTERRUPT_HOSTPORT)
#define FIQ_VIDEOSCALER       (FIQ_START+INTERRUPT_VIDEOSCALER)
#define FIQ_CCP2TX            (FIQ_START+INTERRUPT_CCP2TX)
#define FIQ_SDC               (FIQ_START+INTERRUPT_SDC)
#define FIQ_DSI0              (FIQ_START+INTERRUPT_DSI0)
#define FIQ_AVE               (FIQ_START+INTERRUPT_AVE)
#define FIQ_CAM0              (FIQ_START+INTERRUPT_CAM0)
#define FIQ_CAM1              (FIQ_START+INTERRUPT_CAM1)
#define FIQ_HDMI0             (FIQ_START+INTERRUPT_HDMI0)
#define FIQ_HDMI1             (FIQ_START+INTERRUPT_HDMI1)
#define FIQ_PIXELVALVE1       (FIQ_START+INTERRUPT_PIXELVALVE1)
#define FIQ_I2CSPISLV         (FIQ_START+INTERRUPT_I2CSPISLV)
#define FIQ_DSI1              (FIQ_START+INTERRUPT_DSI1)
#define FIQ_PWA0              (FIQ_START+INTERRUPT_PWA0)
#define FIQ_PWA1              (FIQ_START+INTERRUPT_PWA1)
#define FIQ_CPR               (FIQ_START+INTERRUPT_CPR)
#define FIQ_SMI               (FIQ_START+INTERRUPT_SMI)
#define FIQ_GPIO0             (FIQ_START+INTERRUPT_GPIO0)
#define FIQ_GPIO1             (FIQ_START+INTERRUPT_GPIO1)
#define FIQ_GPIO2             (FIQ_START+INTERRUPT_GPIO2)
#define FIQ_GPIO3             (FIQ_START+INTERRUPT_GPIO3)
#define FIQ_I2C               (FIQ_START+INTERRUPT_I2C)
#define FIQ_SPI               (FIQ_START+INTERRUPT_SPI)
#define FIQ_I2SPCM            (FIQ_START+INTERRUPT_I2SPCM)
#define FIQ_SDIO              (FIQ_START+INTERRUPT_SDIO)
#define FIQ_UART              (FIQ_START+INTERRUPT_UART)
#define FIQ_SLIMBUS           (FIQ_START+INTERRUPT_SLIMBUS)
#define FIQ_VEC               (FIQ_START+INTERRUPT_VEC)
#define FIQ_CPG               (FIQ_START+INTERRUPT_CPG)
#define FIQ_RNG               (FIQ_START+INTERRUPT_RNG)
#define FIQ_ARASANSDIO        (FIQ_START+INTERRUPT_ARASANSDIO)
#define FIQ_AVSPMON           (FIQ_START+INTERRUPT_AVSPMON)

#define FIQ_ARM_TIMER         (FIQ_START+INTERRUPT_ARM_TIMER)
#define FIQ_ARM_MAILBOX       (FIQ_START+INTERRUPT_ARM_MAILBOX)
#define FIQ_ARM_DOORBELL_0    (FIQ_START+INTERRUPT_ARM_DOORBELL_0)
#define FIQ_ARM_DOORBELL_1    (FIQ_START+INTERRUPT_ARM_DOORBELL_1)
#define FIQ_VPU0_HALTED       (FIQ_START+INTERRUPT_VPU0_HALTED)
#define FIQ_VPU1_HALTED       (FIQ_START+INTERRUPT_VPU1_HALTED)
#define FIQ_ILLEGAL_TYPE0     (FIQ_START+INTERRUPT_ILLEGAL_TYPE0)
#define FIQ_ILLEGAL_TYPE1     (FIQ_START+INTERRUPT_ILLEGAL_TYPE1)
#define FIQ_PENDING1          (FIQ_START+INTERRUPT_PENDING1)
#define FIQ_PENDING2          (FIQ_START+INTERRUPT_PENDING2)

#define GPIO_IRQ_START	      (HARD_IRQS + FIQ_IRQS)

#define HARD_IRQS	      (64 + 21)
#define FIQ_IRQS              (64 + 21)
#define GPIO_IRQS	      (32*5)

#define NR_IRQS		      HARD_IRQS+FIQ_IRQS+GPIO_IRQS

#endif /* ! __MACH_IRQS_H__ */
