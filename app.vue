<script setup lang="ts">
import easytimer from 'easytimer.js'

type ButtonAction = 'clockLeft' | 'clockRight' | 'zerkLeft' | 'zerkRight'

const bindings: Record<string, ButtonAction> = {
    ShiftLeft: 'clockLeft',
    ShiftRight: 'clockRight',
    KeyZ: 'zerkLeft',
    Slash: 'zerkRight',
}

window.addEventListener('keydown', (e) => {
    const binding = bindings[e.code]
    if (!binding) return

    console.log(binding)

    if (inSetupMode.value && (binding === 'clockLeft' || binding === 'clockRight')) {
        inSetupMode.value = false
        return
    }

    if (binding === 'zerkLeft') {
        clocks.left = new easytimer({
            countdown: true,
            precision: 'secondTenths',
            startValues: {
                seconds: clocks.left.getTimeValues().seconds / 2,
            },
        })
    } else if (binding === 'zerkRight') {
    } else if (binding === 'clockLeft') {
        clocks.right.start()
        clocks.left.pause()
    } else if (binding === 'clockRight') {
        clocks.left.start()
        clocks.right.pause()
    }
})

const inSetupMode = ref(true)
const initialMinutes = useState('initialMinutes', () => 10)
const incrementSeconds = useState('incrementSeconds', () => 0)

const timeOptions = [0, 1, 2, 3, 5, 8, 10, 15, 20, 30, 45, 60, 90, 120]

const sliderMinuteIndex = useState('sliderMinuteIndex', () =>
    timeOptions.indexOf(initialMinutes.value)
)

const sliderSecondsIndex = useState('sliderSecondsIndex', () =>
    timeOptions.indexOf(incrementSeconds.value)
)

const clocks = {
    left: new easytimer({
        countdown: true,
        precision: 'secondTenths',
        startValues: { seconds: initialMinutes.value * 60 },
    }),
    right: new easytimer({
        countdown: true,
        precision: 'secondTenths',
        startValues: { seconds: initialMinutes.value * 60 },
    }),
}

watch(sliderMinuteIndex, (newValue) => {
    initialMinutes.value = timeOptions[newValue]
})

watch(sliderSecondsIndex, (newValue) => {
    incrementSeconds.value = timeOptions[newValue]
})
</script>

<template>
    <div v-if="inSetupMode" class="text-center text-[14vw]">
        {{ initialMinutes }}+{{ incrementSeconds }}
    </div>
    <div v-else class="flex">
        <Clock :clock="clocks.left" />
        <Clock :clock="clocks.right" />
    </div>
</template>
