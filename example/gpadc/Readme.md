# gpadc示例
@使用指南
    @介绍
        gpadc 应用会在板子上验证通过ADC 测量测试点电压的功能。
        在编译前的配置阶段，需要打开BSP中的ADC 功能。
        有两种通过ADC获取电压的接口，默认的使用读接口获取电池电压的方法，为了获取稳定值底层会做平均处理，如果在意接口运行时间而不做平均处理，可以使用control 接口，但个别情况数据会有跳动，测试方法可以通过宏USE_AVERAGE_METHOD配置。
        测试电压默认输出测试点电压，当部分电路有分压电阻时，测试点并不是电源输入点，这时候就需要带入分压计算， 可以参考voltage_div_proc 将测试点电源转换成输入端电源，如果没有分压电阻，测试点电源即输入电压。
        示例中展示了如何设置ADC PINMUX 以及如何通过ADC获取电压的方法（毫伏），而管脚号和ADC通道之间的映射关系可以通过芯片的规格书获取。
      
 @工程说明
        - 编译方法: 进入project目录执行命令`scons --board=<board_name> -j8`， 其中board_name为板子名称，例如编译eh-lb563板子，完整命令为`scons --board=eh-lb563 -j8`
          编译生成的image文件存放在HCPU的build_<board_name>目录下，common工程的用法参考通<<用工程构建方法>>