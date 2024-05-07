# TODO List lab

## resistenza interna
Per misurare la resistenza interna generiamo un'***onda quadra*** 1Vpp $ddp$ e ci mettiamo ai capi di una resistenza $R$ da 50 $\Omega$, detta $Rg$ la resistenza interna del generatore, abbiamo che il voltaggio misurato vale
$$V = \frac{ddp}{R + Rg} R$$ 
Possiamo fittare questo, oppure la Rg è:
$$Rg = R \left( \frac{ddp}{V} - 1 \right)$$

## Settle time per acquisizione multichannel
Generare un'onda ***sinusoidale*** a 20kHz e acquisire 2 canali a 450kS/s

## Controllare ddp
Confermare che il parametro *amplitude* sia effettivamente Vpp, stessa resistenza di prima, se *amplitude*  = 1 mi aspetto $ddp = 0.5$, quindi
$$V = \frac{R}{R + Rg} 0.5$$

## misurare  induttanza e capacità
Con l'elvis, non cè molto da dire

## Controllare che effettivamente il voltaggio salga alla frequenza di cross


## Acquisire dati
Ampiezza, 
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTMzNzkxNzc2OCwxMDE1NjYzMTQ5LDE3MT
IzNjIyNywtMTY0MDkzMTExNl19
-->