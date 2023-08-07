<script setup lang="ts">
import easytimer from 'easytimer.js'

const clockDisplay = ref({
    minutes: '0',
    seconds: '00',
    tenths: '0',
})

const timer = new easytimer({
    countdown: true,
    startValues: { seconds: 600 },
})

const updateDisplay = () => {
    const values = timer.getTimeValues()
    clockDisplay.value.minutes = values.minutes.toString()
    clockDisplay.value.seconds = strPad(values.seconds)
    clockDisplay.value.tenths = values.secondTenths.toString()
}

timer.addEventListener('secondTenthsUpdated', updateDisplay)

const strPad = (num: number) => num.toString().padStart(2, '0')
</script>

<template>
    <template v-if="clockDisplay.minutes">
        {{ clockDisplay.minutes }}<span class="text-red-600">:</span>{{ clockDisplay.seconds }}
    </template>
    <template v-else>
        {{ clockDisplay.seconds }}<span class="text-red-600">.{{ clockDisplay.tenths }}</span>
    </template>
</template>
