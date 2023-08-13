<script setup lang="ts">
import easytimer from 'easytimer.js'

type ButtonAction = 'clockLeft' | 'clockRight' | 'zerkLeft' | 'zerkRight'
type InitialValue = number

const inSetupMode = ref(true)
const clocksAreRunning = ref(false)
const isFullScreen = ref(false)

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
    clocksAreRunning.value = true
    clocks.value.right.start()
    clocks.value.left.pause()
  } else if (binding === 'clockRight') {
    clocksAreRunning.value = true
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

const toggleFullScreen = () => {
  if (isFullScreen.value) {
    document.exitFullscreen()
    isFullScreen.value = false
  } else {
    document.documentElement.requestFullscreen()
    isFullScreen.value = true
  }
}
</script>

<template>
  <button @mousedown="toggleFullScreen" class="absolute right-2 text-3xl text-slate-400 bg-white opacity-80">
    <img v-if="isFullScreen" src="/images/fullscreen-exit.svg" class="h-8" />
    <img v-else src="/images/fullscreen-enter.svg" class="h-8" />
  </button>
  <div v-if="inSetupMode" class="flex text-center text-[20vw] h-screen items-center text-slate-600 leading-none">
    <div class="flex-none w-2/5">
      <ChangeClockValue @mousedown="changeInitialTimeValue('initialMinutes', +1)" :step="+1" />
      {{ initialMinutes }}
      <ChangeClockValue @mousedown="changeInitialTimeValue('initialMinutes', -1)" :step="-1" />
    </div>
    <div class="flex-none w-1/5">+</div>
    <div class="flex-none w-2/5">
      <ChangeClockValue @mousedown="changeInitialTimeValue('incrementSeconds', +1)" :step="+1" />
      {{ incrementSeconds }}
      <ChangeClockValue @mousedown="changeInitialTimeValue('incrementSeconds', -1)" :step="-1" />
    </div>
  </div>
  <div v-else class="flex gap-[1vw]">
    <img
      v-if="clocksAreRunning"
      src="/images/pause-icon.svg"
      class="h-[20vh] absolute left-1/2 transform -translate-x-1/2 bg-white p-3 rounded-[100%]"
    />
    <Clock :key="JSON.stringify(clocks.left.getConfig())" :clock="clocks.left" :isBerserked="isBerserked.left" />
    <Clock :key="JSON.stringify(clocks.right.getConfig())" :clock="clocks.right" :isBerserked="isBerserked.right" />
  </div>
</template>
