<script setup lang="ts">
import Timer from 'easytimer.js';

const props = defineProps<{
    clock: Timer
    isBerserked: boolean
}>()

const isRunning = ref(false)

const clockDisplay = ref({
    minutes: props.clock.getTimeValues().minutes.toString(),
    seconds: props.clock.getTimeValues().seconds.toString().padStart(2, '0'),
    tenths: '0',
})

const updateDisplay = () => {
    const time = props.clock.getTimeValues()
    clockDisplay.value = {
        minutes: time.minutes.toString(),
        seconds: time.seconds.toString().padStart(2, '0'),
        tenths: time.secondTenths.toString(),
    }
}

props.clock.addEventListener('secondTenthsUpdated', updateDisplay)
props.clock.addEventListener('started', () => isRunning.value = true)
props.clock.addEventListener('paused', () => isRunning.value = false)
</script>

<template>
    <div class="flex-none w-1/2 text-center text-[14vw] h-screen flex items-center justify-center text-slate-600"
        :class="{
            'bg-[#e8f5e9] text-[#2e7d32] border-b-[3vh] border-b-[#2e7d32]': isRunning,
            'border-t-[3vh] border-t-red-700': isBerserked,
        }"
    >
        <div v-if="clockDisplay.minutes === '0'">
            {{ clockDisplay.seconds }}<span class="text-[5vw]">.{{ clockDisplay.tenths }}</span>
        </div>
        <div v-else>
            {{ clockDisplay.minutes }}<span :class="{ blinking: isRunning }">:</span>{{ clockDisplay.seconds }}
        </div>
    </div>
</template>
