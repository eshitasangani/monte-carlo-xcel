<AutoPilot:project xmlns:AutoPilot="com.autoesl.autopilot.project" projectType="C/C++" name="monte-carlo.prj" top="dut">
    <includePaths/>
    <libraryFlag/>
    <files>
        <file name="../../monte-carlo_test.cpp" sc="0" tb="1" cflags=" -std=c++11 -Wno-unknown-pragmas" csimflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="monte-carlo.cpp" sc="0" tb="false" cflags="-std=c++11" csimflags="" blackbox="false"/>
    </files>
    <solutions>
        <solution name="solution1" status=""/>
    </solutions>
    <Simulation argv="">
        <SimFlow name="csim" setup="false" optimizeCompile="true" clean="false" ldflags="" mflags=""/>
    </Simulation>
</AutoPilot:project>

