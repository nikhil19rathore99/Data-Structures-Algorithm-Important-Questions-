import java.util.*;
import java.util.concurrent.Semaphore;
class ProducerConsumer{
    static class Q{
        static Semaphore consume = new Semaphore(0);
        static Semaphore produce = new Semaphore(1);
        int item;
        void Consume(){
            try {
                consume.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Consumed item : " + item);
            produce.release();
        }

        void Produce(int i){
            try {
                produce.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            this.item=i;
            System.out.println("Produce item : " + i);
            consume.release();
        }
    }
    static class Producer implements Runnable{
        Q q;
        Producer(Q q){
            this.q = q;
            new Thread(this,"Producer").start();
        }
        @Override
        public void run(){
            for(int i=0;i<10;i++){
                q.Produce(i);
            }
        }
    }
    static class Consumer implements Runnable{
        Q q;
        Consumer(Q q){
            this.q = q;
            new Thread(this,"Consumer").start();
        }
        @Override
        public void run(){
            for(int i=0;i<10;i++) q.Consume();
        }
    }
    public static void main(String[] args) {
        Q q = new Q();
        Producer p = new Producer(q);
        Consumer c = new Consumer(q);
    }
}