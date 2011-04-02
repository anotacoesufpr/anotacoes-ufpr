set numSwitchesFilhos 5
set maquinasPorSwitch 10
set velocidadeRede 10Mb
# variar 1/10/100/1000 ms
set delayTransmissao 1000ms
set traceOutArq out1ms.tr
set receptores 10
set transmissores 30
set tempoTempoSimulacao 181.0
set tempoStop 180.0
set packSize 1000
set intervaloEntrePacotes 0.05

# cria objeto simulador
set ns [new Simulator]

#Inicializa o arquivo de trace
set traceOut [open out$delayTransmissao.tr w]
$ns trace-all $traceOut

# abre o arquivo trace do nam
#-set nf [open out.nam w]
#-$ns namtrace-all $nf

# define a função finish
proc finish {} {
#	global ns nf
	global ns
	$ns flush-trace
#-	close $nf
#-	exec nam out.nam &
	exit 0
}


# cria switche pai
set pai [$ns node]
#- $pai shape box

# cria os switches filhos
for {set i 0} {$i < $numSwitchesFilhos} {incr i} {
	set switchesFilho($i) [$ns node]
#-	$switchesFilho($i) shape box

}

# liga os switches filhos ao pai e pendura as maquinas neles
for {set i 0} {$i < $numSwitchesFilhos} {incr i} {
        $ns duplex-link $switchesFilho($i) $pai $velocidadeRede $delayTransmissao DropTail
        for {set x 0} {$x < $maquinasPorSwitch} {incr x} {
		#gera o numero da maquina que fai no switch
                set numMaquinas [expr ($i * $maquinasPorSwitch + $x)]
	
                set maquinas($numMaquinas) [$ns node]
                $ns duplex-link $switchesFilho($i) $maquinas($numMaquinas) $velocidadeRede $delayTransmissao DropTail
        }
}


# define os receptores aleatoriamente
set recep 0
while {$recep < $receptores} {
        set num [expr { int($numMaquinas * rand()) }]
        if { [info exists maquinasUsadas($num)] } {
                #Maquina ja utilizada
        } else {
                set maquinasUsadas($num) 1
		set receptoresList($recep) [new Agent/Null]
		$ns attach-agent $maquinas($num) $receptoresList($recep)
#- $maquinas($num) color blue
		incr recep
        }
}


# define os transmissores aleatoriamente
set trans 0
while {$trans < $transmissores} {
        set num [expr { int($numMaquinas * rand()) }]
        if { [info exists maquinasUsadas($num)] } {
                #Maquina ja utilizada
        } else {
                set maquinasUsadas($num) 1
                set udpList($trans) [new Agent/UDP]
                $ns attach-agent $maquinas($num) $udpList($trans)
#- $maquinas($num) color Red
                set cbrList($trans) [new Application/Traffic/CBR]
                $cbrList($trans) set packetSize_ $packSize
                $cbrList($trans) set interval_ $intervaloEntrePacotes
                $cbrList($trans) attach-agent $udpList($trans)

                set indice [expr $trans % $receptores]
                $ns connect $udpList($trans) $receptoresList($indice)

		$ns at 0.0 "$cbrList($trans) start"
		$ns at $tempoStop "$cbrList($trans) stop"
                incr trans
        }
}

$ns at $tempoTempoSimulacao "finish"

$ns run

