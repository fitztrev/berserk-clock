<script setup lang="ts">
import easytimer from 'easytimer.js'

type ButtonAction = 'clockLeft' | 'clockRight' | 'zerkLeft' | 'zerkRight'
type InitialValue = number

const inSetupMode = ref(true)

const initialMinutes: Ref<InitialValue> = useState('initialMinutes', () => 10)
const incrementSeconds: Ref<InitialValue> = useState('incrementSeconds', () => 0)

const clocks = ref({
  left: new easytimer(),
  right: new easytimer(),
})

const isBerserked = ref({
  left: false,
  right: false,
})

const bindings: Record<string, ButtonAction> = {
  Digit1: 'clockLeft',
  Digit2: 'clockRight',
  Digit3: 'zerkLeft',
  Digit4: 'zerkRight',
}

const playSound = (name: 'Berserk') => {
  const audio = new Audio(`/sound/${name}.mp3`)
  audio.play()
}

window.addEventListener('keydown', (e) => {
  const binding = bindings[e.code]
  if (!binding) return

  console.log(binding)

  if (inSetupMode.value && (binding === 'clockLeft' || binding === 'clockRight')) {
    inSetupMode.value = false

    clocks.value.left = new easytimer({
      countdown: true,
      precision: 'secondTenths',
      startValues: { seconds: initialMinutes.value * 60 },
    })

    clocks.value.right = new easytimer({
      countdown: true,
      precision: 'secondTenths',
      startValues: { seconds: initialMinutes.value * 60 },
    })
    return
  }

  if (binding === 'zerkLeft') {
    clocks.value.left = new easytimer({
      countdown: true,
      precision: 'secondTenths',
      startValues: {
        seconds: (initialMinutes.value / 2) * 60,
      },
    })
    isBerserked.value.left = true
    playSound('Berserk')
  } else if (binding === 'zerkRight') {
    clocks.value.right = new easytimer({
      countdown: true,
      precision: 'secondTenths',
      startValues: {
        seconds: (initialMinutes.value / 2) * 60,
      },
    })
    isBerserked.value.right = true
    playSound('Berserk')
  } else if (binding === 'clockLeft') {
    clocks.value.right.start()
    clocks.value.left.pause()
  } else if (binding === 'clockRight') {
    clocks.value.left.start()
    clocks.value.right.pause()
  }
})

const changeInitialTimeValue = (store: 'initialMinutes' | 'incrementSeconds', delta: number) => {
  const value = useState(store) as Ref<InitialValue>
  console.log(value.value)
  const timeOptions = [0, 1, 2, 3, 5, 8, 10, 15, 20, 30, 45, 60, 90, 120]
  const index = timeOptions.indexOf(value.value)
  const newIndex = Math.max(0, Math.min(timeOptions.length - 1, index + delta))
  value.value = timeOptions[newIndex]
}
</script>

<template>
  <div v-if="inSetupMode" class="flex text-center text-[12vw] h-screen items-center text-slate-600">
    <div class="flex-none w-2/5">
      <button @click="changeInitialTimeValue('initialMinutes', +1)" class="text-slate-200">&#9650;</button>
      <br />
      {{ initialMinutes }}
      <br />
      <button @click="changeInitialTimeValue('initialMinutes', -1)" class="text-slate-200">&#9660;</button>
    </div>
    <div class="flex-none w-1/5">+</div>
    <div class="flex-none w-2/5">
      <button @click="changeInitialTimeValue('incrementSeconds', +1)" class="text-slate-200">&#9650;</button>
      <br />
      {{ incrementSeconds }}
      <br />
      <button @click="changeInitialTimeValue('incrementSeconds', -1)" class="text-slate-200">&#9660;</button>
    </div>
  </div>
  <div v-else class="flex gap-[1vw]">
    <Clock :key="JSON.stringify(clocks.left.getConfig())" :clock="clocks.left" :isBerserked="isBerserked.left" />
    <Clock :key="JSON.stringify(clocks.right.getConfig())" :clock="clocks.right" :isBerserked="isBerserked.right" />
  </div>
</template>
